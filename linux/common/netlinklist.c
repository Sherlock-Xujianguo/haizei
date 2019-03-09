#include "netlinklist.h"


void insert_node(char *name, struct sockaddr_in addr, Linklist *l) {
    if (l -> head == NULL) {
        Node* n = (Node*)malloc(sizeof(Node));
        n -> next = NULL;
        strcpy(n -> user_info.ip, inet_ntoa(addr.sin_addr));
        strcpy(n -> user_info.name, name);
        l -> head = n;
        l -> num++;
    } else {
        Node* n = l -> head;
        while (n -> next != NULL) n = n -> next;
        Node* p = (Node*)malloc(sizeof(Node));
        p -> next = NULL;
        strcpy(p -> user_info.ip, inet_ntoa(addr.sin_addr));
        strcpy(p -> user_info.name, name);
        n -> next = p;
        l -> num++;
    }
}

void del_node(char *name, Linklist *l) {
    if (l -> head == NULL) return ;
    else {
        Node* n = l -> head;
        while (strcmp(n -> user_info.name, name) != 0 && n -> next != NULL) {
            n = n -> next;
        }
        if (n -> next == NULL && strcmp(n -> user_info.name, name) != 0) return ;
        else {
            if (n == l -> head) {
                l -> head = n -> next;
                free(n);
                l -> num--;
                return ;
            } else {
                Node* temp = l -> head;
                while (temp -> next != n) temp = temp -> next;
                temp -> next = n -> next;
                free(n);
                l -> num--;
                return ;
            }
        }
    }
}

