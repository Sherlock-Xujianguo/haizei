#include "./common.h"

int write_pi_log(char *PiHealthLog, const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    FILE *fp;
    if ((fp = fopen(PiHealthLog, "a+")) < 0) {
        perror("open PiHealthLog file failed!\n");
        return -1;
    }
    time_t timer;
    struct tm *tblock;
    timer = time(NULL);
    tblock = localtime(&timer);
    fprintf(fp, "%d-%02d-%02d~%02d:%02d:%02d# ", tblock->tm_year+1900, tblock->tm_mon+1, tblock->tm_mday,tblock->tm_hour,tblock->tm_min,tblock->tm_sec);
    vfprintf(fp, format, arg);
    fclose(fp);
    va_end(arg);
}

int get_conf_info(const char *pathname,const char *key_name, char * dest) {
     FILE *fp = fopen(pathname, "r");
     if (fp == NULL) {
         printf("File %s doesn't exsit\n", pathname);
         return -1;
     }
     char *line = NULL;
     size_t len = 0;
     ssize_t read;
     while ((read = getline(&line, &len, fp)) != -1) { 
        char *temp_name = (char *)malloc(sizeof(char)*1024);
        int i;
        for (i = 0; i < len; i++) {
            if (line[i] == '=' || line[i] == '\n' || i == len - 1) {
                temp_name[i] = '\0';
                break;
            }
            else temp_name[i] = line[i];
        }
        if (strcmp(temp_name, key_name) == 0) {
            int temp_len = 0;
            for (i = i + 1; i < len; i++) {
                if (i == len - 1 || line[i] == '\n') {
                    dest[temp_len] = '\0';
                    free(temp_name);
                    return 1;
                }
                else {
                    dest[temp_len] = line[i];
                    temp_len++;
                }
            }
        }
        free(temp_name);
     }
     free(line);
     return -1;
}


int create_send_socket(int port, char *ip) {
    int fd;
    if ( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("send socket create error");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int con = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (con < 0) {
        perror("connect error");
        close(fd);
        return -1;
    }
    return fd;
}

int create_recv_socket(int port) {
    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("recv socket create error");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind error");
        close(fd);
        return -1;
    }
    if (listen(fd, 30) < 0) {
        perror("listen error");
        close(fd);
        return -1;
    }
    return fd;
}

int insert_node(node *n, Linklist *l) {
	node *p = *l;
	while (p != NULL) {
		if (strcmp(n -> client_info.ip, p -> client_info.ip) == 0) {
			printf("%s has logged in.\n", n -> client_info.ip);
			return -1;
		}
		p = p -> next;
	}
	n -> next = *l;
	*l = n;
	printf("%s logged in.\n", (*l) -> client_info.ip);
	return 1;
}

void del_node(node *n, Linklist *l) {
	node *p = *l;
	while (p) {
		if (strcmp(n -> client_info.ip, p -> client_info.ip) == 0) {
			if (p == *l) {
				*l = p -> next;
				printf("delete %s successfully\n", p -> client_info.ip);
				free(p);
				return ;
			} else {
				node *pre = *l;
				while (pre -> next != p) pre = pre -> next;
				pre -> next = p -> next;
				free(p);
				return ;
			}
		}
		p = p -> next;
	}
}