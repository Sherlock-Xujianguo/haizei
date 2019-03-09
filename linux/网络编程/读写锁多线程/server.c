#include "./common.h"
Linklist l;

void send_to(char *name, char *temp) {
	node *p = l;
	char ip[20];
	while (strcmp(p -> name, name) != 0 && p != NULL) {
		p = p -> next;
	}
	if (p == NULL) {
		printf("can't find %s\n", name);
		return ;
	}
	else {
		strcpy(ip, p -> ip);
	}
	char *tmp = (char*)malloc(sizeof(char)*1024);
	get_conf_info("./chat.conf","client_port",tmp);
	int client_port = atoi(tmp);
	free(tmp);
	int fd;
	if ((fd = create_send_socket(client_port, ip)) < 0) {
		printf("can't connect to %s\n", name);
	}
	send(fd, temp, sizeof(struct Message), 0);
	close(fd);
}

void send_all(char *buf) {
	node *p = l;
	char *tmp = (char*)malloc(sizeof(char)*1024);
	get_conf_info("./chat.conf","client_port",tmp);
	int client_port = atoi(tmp);
	free(tmp);
	while (p != NULL) {
		char ip[20];
		strcpy(ip, p -> ip);
		int fd;
		if ((fd = create_send_socket(client_port, ip)) < 0) {
			printf("can't connect to %s\n", p -> name);
			p = p -> next;
			close(fd);
			continue;
		}
		send(fd, buf, sizeof(struct Message), 0);

		close(fd);
		p = p -> next;
	}
}

void *add_node(void *n) {
	node *p = (node *)n;
	insert_node(p, &l);

	struct Message m;
	strcpy(m.name, "server");
	m.flag = 1;
	strcpy(m.message, "welcome to our chat room!");
	char *temp = (char *)malloc(sizeof(m));
	memcpy(temp, &m, sizeof(m));
	send_to(p -> name, temp);
	free(temp);

	while (1) {
		int recv_fd;
		char *buf = (char*)malloc(sizeof(struct Message));
		recv_fd = recv(p -> fd, buf, sizeof(struct Message), 0);
		if (recv_fd > 0) {
			struct Message m;
			memcpy(&m, buf, sizeof(m));
			printf("%s : %s\n", m.name, m.message);
			if (m.flag == 0) {
				send_all(buf);
			}
		} else if (recv_fd == 0) {
			printf("%s logged out\n", p -> name);
			close(recv_fd);
			free(buf);
			break;
		}
		free(buf);
	}
}

void *print() {
	while (1) {
		sleep(30);
		int total = 0;
		node *p = l;
		fflush(stdout);
		printf("*****************************************\n");
		while (p != NULL) {
			printf("%s -> %d\n", p -> name, p -> fd);
			total++;
			p = p -> next;
		}
		printf("Now %d users is online\n", total);
		printf("*****************************************\n");
	}
}

int main()
{
	l = NULL;
	char *temp = (char *)malloc(sizeof(char) * 1024);
	get_conf_info("./chat.conf","server_port",temp);
	int port = atoi(temp);
	free(temp);
	int recv_fd;
	if ((recv_fd = create_recv_socket(port)) < 0) {
		printf("Can't create receive socket\n");
		close(recv_fd);
		return -1;
	}

	pthread_t print_t, add_t;
	pthread_create(&print_t, NULL, print, NULL);
	while (1) {
		struct sockaddr_in addr;
		int len;
		int fd;
		if ((fd = accept(recv_fd, (struct sockaddr*)&addr, &len)) > 0){
			char name[20];
			recv(fd, name, 20, 0);
			node *n = (node*)malloc(sizeof(node));
			n -> fd = fd;
			strcpy(n -> name, name);
			n -> next = NULL;
			strcpy(n -> ip, inet_ntoa(addr.sin_addr));
			printf("%s log in!Say hello to him or her\n", name);
			pthread_create(&add_t, NULL, add_node, (void *)n);
		}
	}
	pthread_join(print_t, NULL);
	return 0;
}