#include "../common/common.h"
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
    char message[size];
};

struct user {
    char name[20];
    char ip[20];
} users[30];
int u_num = 0;

void add_user(struct sockaddr_in addr, char *name) {
     strcpy(users[u_num].name, name);
     strcpy(users[u_num].ip, inet_ntoa(addr.sin_addr));
     printf("hello %s from %s\n", users[u_num].name, users[u_num].ip);
     u_num++;
}

char* get_tar_name(char *buf) {
    char *temp = (char *)malloc(sizeof(char) * 20);
    for (int i = 1; i < strlen(buf); i++) {
        if (buf[i] == ' ') {
            temp[i - 1] = '\0';
            return temp;
        } else {
            temp[i - 1] = buf[i];
        }
    }
}

void get_tar_message(char *m, char *buf) {
    int i;
    for (i = 0; i < strlen(buf); i++) {
        if (buf[i] == ' ') break;
    }
    int len = 0;
    for (i++; i < strlen(buf); i++, len++) {
        m[len] = buf[i];
    }
    m[len] = '\0';
}

int send_message(char *tar_name, char *m) {

    for (int i = 0; i < u_num; i++) {
        if (strcmp(users[i].name, tar_name) == 0) {
            int send_fd = create_send_socket(client_port, users[i].ip);
            if (send_fd < 0) {
                close(send_fd);
                return -1;
            }
            char final_message[size] = {0};
            strcat(final_message, tar_name);
            strcat(final_message, ": ");
            strcat(final_message, m);
            if (write(send_fd, final_message, strlen(final_message)) > 0) {
                close(send_fd);
                return 1;
            }
            close(send_fd);
        }
        return -1;
    }
}

void send_all(char *buf){
    for (int i = 0; i < u_num; i++) {
        int send_fd = create_send_socket(client_port, users[i].ip);
        if (send_fd < 0) {
            close(send_fd);
            continue;
        }
        write(send_fd, buf, strlen(buf));
        close(send_fd);
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
}

void work(int recv_fd) {
    char buf[size];
    while (1) {
        memset(buf, 0, sizeof(buf));
        int read_flag = read(recv_fd, buf, size-1);
        if (read_flag < 0) {
            perror("read error");
            break;
        } else if (read_flag == 0) {
            break;
        } else {
            if (buf[0] == '@') {
                char *tar_name = NULL;
                tar_name = get_tar_name(buf);
                char m[size] = {0};
                get_tar_message(m, buf);
                send_message(tar_name, m);
                free(tar_name);
            } else {
                send_all(buf);
            }
        }
    }
    close(recv_fd);
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
            //将用户加入队列

            char name[20] = {0};
            read(recv_fd, name, 19);
            int fid = fork();
            if (fid == -1) {
                perror("fork error");
                close(recv_fd);
                break;
            }
            if (fid == 0) {
                add_user(recv_addr, name);
                close(fd);
                work(recv_fd);
                //将用户移除队列
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

