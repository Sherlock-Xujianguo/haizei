#include "../common/common.h"
#include <pthread.h>
#include <inttypes.h>
#define max_n 100

int64_t end, now=0, start, sum=0;
pthread_mutex_t now_t;

void *add() {
    while (1) {
        pthread_mutex_lock(&now_t);
        if (now > end) {
            pthread_mutex_unlock(&now_t);
            break;
        }
        sum += now;
        now++;
        pthread_mutex_unlock(&now_t);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("./a.out num num_of_pthread\n");
        return -1;
    }
    int num_of_pthread = 0;
    num_of_pthread =  atoi(argv[2]);
    end = atoi(argv[1]);
    pthread_t tid[max_n];

    for (int i = 0; i < num_of_pthread; i++) {
        pthread_create(&tid[i], NULL, add, NULL);
    }
    
    for (int i = 0; i < num_of_pthread; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("sum = %ld\n", sum);
    return 0;
}

