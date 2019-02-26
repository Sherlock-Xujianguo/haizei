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
typedef struct{
    char ip[20];
    char name[20];
}User;

typedef struct node{
    User user_info;
    struct node* next;
}Node;

typedef struct{
    Node* head;
    int num;
}Linklist;



void insert_node(char *name, struct sockaddr_in addr, Linklist *l);

void del_node(char *name, Linklist *l);


