#include "./common.h"

void *heartbeat() {
	char *tmp = (char*)malloc(sizeof(char) * 1024);
	get_conf_info("./conf", "client_port", tmp);
	int client_port = atoi(tmp);
	free(tmp);

	printf("%d\n", client_port);
	int fd;
	fd = create_recv_socket(client_port);
	struct sockaddr_in addr;
	int len;
	while (1) {
		int recv_fd;
		if ((recv_fd = accept(fd, (struct sockaddr*)&addr, &len)) > 0) {
			char buf[1024];
			if (recv(recv_fd, buf, sizeof(buf), 0) == 0) {
				close(recv_fd);
				continue;
			}
		}
	}
}

int main() {
	int fd;
	char *tmp = (char*)malloc(sizeof(char)*1024);
	get_conf_info("./conf", "master_port", tmp);
	int master_port = atoi(tmp);
	char ip[20];
	get_conf_info("./conf", "master_ip", tmp);
	strcpy(ip, tmp);
	free(tmp);
	printf("%s %d\n", ip, master_port);

	pthread_t hb;
	pthread_create(&hb, NULL, heartbeat, NULL);

	fd = create_send_socket(master_port, ip);

	sleep(10);

	close(fd);
	return 0;
}