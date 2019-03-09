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

typedef struct Node {
    int fd;
    char name[20];
    char ip[20];
    struct Node *next;
}node, *Linklist;

struct Message {
    char name[20];
    int flag;
    char message[1024];
};

int get_conf_info(const char *pathname,const char *key_name,char * dest);

int create_send_socket(int port, char *ip);

int create_recv_socket(int port);

void insert_node(node *n, Linklist *l);

void del_node(int fd, Linklist l);