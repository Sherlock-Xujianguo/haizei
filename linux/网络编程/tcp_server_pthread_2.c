#include "../common/common.h"

struct Message {
    char from[20];
    int flag;
    char message[1024];
};

typedef struct Node {
    int fd;
    char name[20];
    struct Node *next;
}Node, *Linklist;

Linklist insert(Linklist head, Node *node) {
    Node *p;
    p = head;
    while (p -> next != NULL) {
        p = p -> next;
    }
    p -> next = node;


    return head;
}

void delte(Linklist head, char *name) {
    Node *p;
    p = head;
    while (p -> next != NULL && strcmp(p -> next.name, name) == 0) {
        p = p -> next;
    }
    if (p -> next == NULL) {
        return ;
    }
    q = p -> next;
    p -> next = p -> next -> next;
    free(q);
}

int main() {
    Linklist linklist;
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p -> name, "init");
    p -> next = NULL;
    linklist = p;
    
    int socketfd;
    char temp_port[5] = {0};

    if ((socketfd = create_recv_socket(server_port)) < 0) {
        perror("create socket error");

    }
    
    
    
    
    return 0;
}
