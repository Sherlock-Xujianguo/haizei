#include "./common.h"

void *send_message() {
	char *temp = (char *)malloc(sizeof(char) * 1024);
	get_conf_info("./chat.conf","server_port",temp);
	int server_port = atoi(temp);
	free(temp);
	char server_ip[1024];
	get_conf_info("./chat.conf", "server_ip", server_ip);
	int fd = create_send_socket(server_port, server_ip);
	if (fd < 0) {
		printf("Can't send message\n");
		return NULL;
	}
	char my_name[20];
	get_conf_info("./chat.conf","my_name",my_name);
	send(fd, my_name, sizeof(my_name), 0);

	while (1) {
		struct Message m;
		strcpy(m.name, my_name);
		char buf[1024];
		for (int i = 0; i < 1024; i++) {
			buf[i] = getchar();
			if (buf[i] == '\n') {
				buf[i] = '\0';
				break;
			}
		}
		if (strcmp(buf, "close") == 0) {
			close(fd);
			return NULL;
		}
		buf[1023] = '\0';
		if (buf[0] == '@') m.flag = 1;
		else m.flag = 0;
		strcpy(m.message, buf);
		char *send_arr = (char *)malloc(sizeof(m));
		memcpy(send_arr, &m, sizeof(m));
		send(fd, send_arr, sizeof(m), 0);
	}
}


int main() {
	pthread_t send_pthread;
	pthread_create(&send_pthread, NULL, send_message, NULL);

	char *temp = (char *)malloc(sizeof(char) * 1024);
	get_conf_info("./chat.conf","client_port",temp);
	int client_port = atoi(temp);
	free(temp);
	int recv_fd = create_recv_socket(client_port);
	if (recv_fd < 0) {
		printf("Can't receive messages, but you can still send messages.\n");
		pthread_join(send_pthread, NULL);
		return -1;
	} 

	while (1) {
		struct sockaddr_in addr;
		int len;
		int fd = accept(recv_fd, (struct sockaddr*)&addr, &len);
		printf("someone connect\n");
		if (fd > 0) {
			struct Message m;
			char *buf = (char *)malloc(sizeof(m));
			recv(fd, buf, sizeof(m), 0);
			memcpy(&m, buf, sizeof(m));
			printf("%s : %s\n", m.name, m.message);
			fflush(stdout);
			if (strcmp(m.message, "close") == 0) {
				close(fd);
				break;
			}
		}
		close(fd);
	}

	pthread_join(send_pthread, NULL);
	return 0;
}