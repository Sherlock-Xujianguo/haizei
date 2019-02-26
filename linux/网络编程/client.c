#include "../common/common.h"
#define size 1024
char *server_ip = NULL;
int server_port;
int client_port;
char *my_name = NULL;
char *log_file = NULL;
char *pathname = "../conf/net.conf";

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
                char buf[size] = {0};
                read(recv_fd, buf, size - 1);
                printf("%s\n", buf);
            }
            close(recv_fd);
        }
    } else {
        int fd;
        if ((fd = create_send_socket(server_port, server_ip)) < 0) {
            return -1;
        }
        while (1) {
            char buf[size] = {0};
            for (int i = 0; i < size; i++) {
                buf[i] = getchar();
                if (buf[i] == '\n') {
                    buf[i] = '\0';
                    break;
                }
            }
            buf[1024] = '\0';
            if (strcmp(buf, "close") == 0) break;
            write(fd, buf, strlen(buf));
        }
        close(fd);
        exit(0);
    }
        return 0;
}

