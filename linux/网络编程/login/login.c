#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *ip = argv[1];
    int port = atoi(argv[2]);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        printf("socket error\n");
        return  -1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int addrlen = sizeof(addr);
    int listen_socket = connect(fd, (struct sockaddr *)&addr, addrlen);
    if (listen_socket == -1) {
        printf("connect error\n");
        return -1;
    }

    char buf[1024];
    char *name = "徐浩然";
    send(fd, name, strlen(name)+1, 0);
    while (1) {
        scanf("%s", buf);
        if (strcmp("close", buf) == 0) {
            char *temp = "[徐浩然]因言语过激被踢出直播间";
            send(fd, temp, strlen(temp), 0);
            break;
        }
        send( fd, buf, strlen(buf), 0);
    }
    close(listen_socket);
    return 0;
}

