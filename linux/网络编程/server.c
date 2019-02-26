#include "../common/common.h"
#include "../common/netlinklist.h"
#define size 1024

int client_port;
int server_port;
char *server_ip;
char *my_name;
char *log_file;
char *pathname = "../conf/net.conf";

struct Message {
    char from[20];
    int flag;
    char message[100];
};

Linklist *l;

char* get_tar_name(char *buf) {
    char *temp = (char *)malloc(sizeof(char) * 20);
    for (int i = 1; i <= strlen(buf); i++) {
        if (buf[i] == ' ' || buf[i] == '\0') {
            temp[i - 1] = '\0';
            return temp;
        } else {
            temp[i - 1] = buf[i];
        }
    }
}

int send_message(char *buf) {
    struct Message *m;
    m = (struct Message *)buf;
    char *tar_name = get_tar_name(m -> message);
    Node *n = l -> head;
    while (n != NULL) {
        if (strcmp(n -> user_info.name, tar_name) == 0) {
            int send_fd = create_send_socket(client_port, n -> user_info.ip);
            if (send_fd < 0) {
                close(send_fd);
                return -1;
            }
            if (send(send_fd, buf, size, 0) > 0) {
                printf("%s : %s\n", m -> from, m -> message);
                close(send_fd);
                return 1;
            }
            close(send_fd);
        }
        return -1;
    }
}

void send_all(char *buf){
    Node* n = l -> head;
    while (n != NULL) {
        int send_fd = create_send_socket(client_port, n -> user_info.ip);
        if (send_fd < 0) {
            perror("create_send_socket error");
            close(send_fd);
            continue;
        }
        send(send_fd, buf, size, 0);
        struct Message *m = (struct Message *)buf;
        printf("%s : %s\n", m -> from, m -> message);
        close(send_fd);
        n = n -> next;
    }
}

void init() {
    char *temp;
    temp = get_conf_info(pathname, "client_port", size);
    client_port = atoi(temp);
    free(temp);
    temp = get_conf_info(pathname, "server_port", size);
    server_port = atoi(temp);
    free(temp);
    server_ip = get_conf_info(pathname, "server_ip", size);
    log_file =get_conf_info(pathname, "log_file", size);
    l = (Linklist*)malloc(sizeof(Linklist));
    l -> head = NULL;
    l -> num = 0;
}

void work(int recv_fd) {
    char buf[size];
    while (1) {
        memset(buf, 0, sizeof(buf));
        int read_flag = recv(recv_fd, buf, size, 0);
        if (read_flag < 0) {
            perror("read error");
            break;
        } else if (read_flag == 0) {
            break;
        } else {
            struct Message *m;
            m = (struct Message*)buf;
            FILE *fp = fopen(log_file, "a+");
            if (fp != NULL) {
                fputs(m -> from, fp);
                fputs(": ", fp);
                fputs(m -> message, fp);
                fputs("\n", fp);
            }
            fclose(fp);

            if (m -> message[0] == '@') {
                send_message(buf);
            } else {
                send_all(buf);
            }
        }
    }
    close(recv_fd);
}

void print() {
    printf("\n");
    Node* n = l -> head;
    while (n != NULL) {
        printf("%s : %s\n", n -> user_info.name, n -> user_info.ip);
        n = n -> next;
    }
    printf("\n");
}


int main()
{
    init();

    int fd;
    if ((fd = create_recv_socket(server_port)) < 0) {
        return -1;
    }

    printf("等待连接：\n");
    while (1) {
        int recv_fd;
        struct sockaddr_in recv_addr;
        int addr_len = sizeof(recv_addr);
        if ((recv_fd = accept(fd, (struct sockaddr*)&recv_addr, &addr_len)) > 0) {
            char name[20] = {0};
            recv(recv_fd, name, 19, 0);
            int fid = fork();
            if (fid == -1) {
                perror("fork error");
                close(recv_fd);
                break;
            }
            if (fid == 0) {
                insert_node(name, recv_addr, l);
                close(fd);
                work(recv_fd);
                del_node(name, l);
                printf("good bye\n");               
                break;
            }
            else {
                close(recv_fd);
                continue;
            }
        }
    }
    close(fd);
    return 0;
}

