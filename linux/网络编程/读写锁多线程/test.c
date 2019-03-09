#include <stdio.h>
#include <pthread.h>

long long rst = 0, now = 1, end, thread_num;
pthread_mutex_t id;

void *add() {
    while (1) {
        pthread_mutex_lock(&id);
        if (now > end) {
            pthread_mutex_unlock(&id);
            return NULL;
        }
        rst += now;
        now ++;
        pthread_mutex_unlock(&id);
    }
    return NULL;
}



int main()
{
    scanf("%lld%lld", &end , &thread_num);
    pthread_t thread[100];
    for (int i = 0; i < thread_num; i++) {
        pthread_create(&thread[i], NULL, add, NULL);
    }

    for (int i = 0; i < thread_num; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("%lld\n", rst);

    return 0;
}

