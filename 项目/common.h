#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

struct client {
    char ip[20];
};

typedef struct Node {
	struct client client_info;
	struct Node *next;
}node, *Linklist;

int write_pi_log(char *PiHealthLog, const char *format, ...);

int get_conf_info(const char *pathname,const char *key_name,char * dest);

int create_send_socket(int port, char *ip);

int create_recv_socket(int port);

int insert_node(node *n, Linklist *l);

void del_node(node *n, Linklist *l);

