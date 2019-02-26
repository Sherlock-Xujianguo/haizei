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

char* get_conf_info(const char *pathname,const char *key_name,const int size);

int create_send_socket(int port, char *ip);

int create_recv_socket(int port);
