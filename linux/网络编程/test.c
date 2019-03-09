#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void *print()
{
    printf("12345\n");
}

int main()
{
    pthread_t id1, id2;
    pthread_create(&id1, NULL, (void *)print, NULL);
    pthread_create(&id2, NULL, (void *)print, NULL);
    pthread_join(&id1, NULL);
    pthread_join(&id2, NULL);
    return 0;
}

