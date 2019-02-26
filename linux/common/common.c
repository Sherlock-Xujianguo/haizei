#include "./common.h"

char *get_conf_info(const char *pathname,const char *key_name, int size) {
     char *temp = (char *)malloc(sizeof(char) * size);
     FILE *fp = fopen(pathname, "r");
     if (fp == NULL) {
         printf("File %s doesn't exsit\n", pathname);
         strcpy(temp, "error");
         return temp;
     }
     char *line = NULL;
     size_t len = 0;
     ssize_t read;
     while ((read = getline(&line, &len, fp)) != -1) { 
        char *temp_name = (char *)malloc(sizeof(char) * size);
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
                    temp[temp_len] = '\0';
                    free(temp_name);
                    return temp;
                }
                else {
                    temp[temp_len] = line[i];
                    temp_len++;
                }
            }
        }
        free(temp_name);
     }
     strcpy(temp, "error");
     free(line);
     return temp;
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
        perror("connect reach max times");
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
