#include "./common.h"

Linklist l = NULL;

struct input {
	int fd;
	char ip[20];
};

pthread_rwlock_t wrlock;

void *count(void *list) {
    Linklist *l = (Linklist *)list;
    while (1) {
        pthread_rwlock_rdlock(&wrlock);
        int total = 0;
        node *p = *l;
        while (p) {
            total++;
            p = p -> next;
        }
        printf("总共有%d个节点\n", total);
        pthread_rwlock_unlock(&wrlock);
        sleep(2);
    }
}

void *heartbeat(void *list) {
	Linklist *l = (Linklist *)list;
	char *tmp = (char*)malloc(sizeof(char) * 1024);
	get_conf_info("./conf", "heartbeat", tmp);
	int sec = atoi(tmp);
	get_conf_info("./conf", "client_port", tmp);
	int client_port = atoi(tmp);
	free(tmp);

	while (1) {
		pthread_rwlock_rdlock(&wrlock);
		node *n = *l;
		while (n) {
			int fd;
			if ((fd = create_send_socket(client_port, n -> client_info.ip)) > 0) {
				close(fd);
				n = n -> next;
				continue;
			} else {
				close(fd);
				sleep(sec);
				if ((fd = create_send_socket(client_port, n -> client_info.ip)) > 0) {
					close(fd);
					n = n -> next;
					continue;
				} else {
					close(fd);
					pthread_rwlock_unlock(&wrlock);
					pthread_rwlock_wrlock(&wrlock);
					del_node(n, l);
					pthread_rwlock_unlock(&wrlock);
					pthread_rwlock_rdlock(&wrlock);
					n = n -> next;
				}
			}
		}
		pthread_rwlock_unlock(&wrlock);
		sleep(sec);
	}
}

void *add_node(void *tmp) {
	struct input *p = (struct input*)tmp;
	node *n = (node*)malloc(sizeof(node));
	strcpy(n -> client_info.ip, p -> ip);
	pthread_rwlock_wrlock(&wrlock);
	if (insert_node(n, &l) < 0) {
		return NULL;
	}
	pthread_rwlock_unlock(&wrlock);
	int recv_fd = p -> fd;
	while (1) {
		char buf[1024];
		if (recv(recv_fd, buf, sizeof(buf), 0) > 0) {
			printf("%s\n", buf);
		} else if (recv(recv_fd, buf, sizeof(buf), 0) == 0) {
			printf("%s logged out\n", n -> client_info.ip);
			break;
		}
	}
	close(recv_fd);
	return NULL;
}

int main()
{
	char *tmp = (char*)malloc(sizeof(char)*1024);
	get_conf_info("./conf", "master_port", tmp);
	int master_port = atoi(tmp);
    int fd;
    if ((fd = create_recv_socket(master_port)) < 0) {
    	perror("create receive socket error");
    	return -1;
    }

    pthread_t hb, cnt;
    pthread_create(&hb, NULL, heartbeat, (void*)&l);
    pthread_create(&cnt, NULL, count, (void*)&l);

    while (1) {
    	struct sockaddr_in addr;
    	int len;
    	pthread_t add_t;
    	int recv_fd;
    	if ((recv_fd = accept(fd, (struct sockaddr*)&addr, &len)) > 0) {
    		struct input *n = (struct input*)malloc(sizeof(struct input));
    		n -> fd = recv_fd;
    		strcpy(n -> ip, inet_ntoa(addr.sin_addr));
    		pthread_create(&add_t, NULL, add_node, (void *)n);
    	}
    }
    return 0;
}

