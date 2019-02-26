#include "../common/common.h"
#define size 1024
char *server_ip = NULL;
int server_port;
int client_port;
char *my_name = NULL;
char *log_file = NULL;
char *pathname = "../conf/net.conf";

struct Message {
    char from[20];
    int flag;
    char message[100];
};

void init() {
    server_ip = get_conf_info(pathname, "server_ip", size);
    my_name = get_conf_info(pathname, "my_name", size);
    log_file = get_conf_info(pathname, "log_file", size);
    char *temp = get_conf_info(pathname, "server_port", size);
    server_port = atoi(temp);
    free(temp);
    temp = get_conf_info(pathname, "client_port", size);
    client_port = atoi(temp);
    free(temp);
}

int main()
{
    init();    
    
    int fid = fork();
    if (fid < 0) {
        perror("fork error");
        return -1;
    }
    else if (fid > 0) {
        int fd;
        if ((fd = create_recv_socket(client_port)) < 0) {
            perror("create recv socket error");
            close(fd);
            exit(-1);
        }
        while (1) {
            struct sockaddr_in addr;
            int len = sizeof(addr);
            int recv_fd = accept(fd, (struct sockaddr*)&addr, &len);
            if (recv_fd > 0) {
                char buf[sizeof(struct Message)];
                recv(recv_fd, buf, sizeof(buf), 0);
                struct Message *m = (struct Message*)buf;
                printf("%s : %s\n", m -> from, m -> message);
            }
            close(recv_fd);
        }
    } else {
        int fd;
        if ((fd = create_send_socket(server_port, server_ip)) < 0) {
            return -1;
        }
        char *name = "徐浩然";
        send(fd, name, strlen(name) + 1, 0);
        while (1) {
            char buf[size] = {0};
            for (int i = 0; i < size; i++) {
                buf[i] = getchar();
                if (buf[i] == '\n') {
                    buf[i] = '\0';
                    break;
                }
            }
            buf[1023] = '\0';
            struct Message m;
            strcpy(m.from, name);
            if (buf[0] == '@') m.flag = 1;
            else m.flag = 0;
            strcpy(m.message, buf);
            if (strcmp(buf, "close") == 0) break;
            char send_m[size];
            memcpy(send_m, &m, sizeof(m));
            send(fd, send_m, size, 0);
        }
        close(fd);
        exit(0);
    }
        return 0;
}

