#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
 
 
#define PORT 9990
#define SIZE 1024

char name[SIZE];

int Creat_socket()
{
	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_socket == -1)
	{
		perror("socket");
		return -1;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	
	addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == -1)
	{
		perror("bind error\n");
		return -1;
	}
	
	ret = listen(listen_socket, 5);
	if(ret == -1)
	{
		perror("listen error\n");
		return -1;
	}
	return listen_socket;
}
 
int wait_client(int listen_socket)
{
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(cliaddr);
	printf("等待客户端连接\n");
	int client_socket = accept(listen_socket, (struct sockaddr *)&cliaddr, &addrlen);   //创建一个和客户端交流的套接字
	if(client_socket == -1)
	{
		perror("accept error\n");
		return -1;
	}
	
	printf("成功接收到一个客户端：%s\n", inet_ntoa(cliaddr.sin_addr));
	
	return client_socket;
}
 
void hanld_client(int client_socket)
{
	char buf[SIZE];
    int ret = read(client_socket, buf, SIZE-1);
    buf[ret] = '\0';
    strcpy(name, buf);
	while(1)
	{
		int ret = read(client_socket, buf, SIZE-1);
		if(ret == -1)
		{
			perror("read error\n");
			break;
		}
		if(ret == 0)
		{
			break;
		}
		buf[ret] = '\0';
		
		printf("%s:%s\n", name, buf);
		
	}
    printf("%s断开连接\n", name);
	close(client_socket);
}
 
int main()
{
	int listen_socket = Creat_socket();
	
    while (1) {
        int client_socket = wait_client(listen_socket);
        int pid = fork();
        if (pid > 0) {
            close(client_socket);
            continue;
        }
        if (pid == 0) {
            close(listen_socket);
            hanld_client(client_socket);
            break;
        }
    }
	
	close(listen_socket);
	
	return 0;
}
