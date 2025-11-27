#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t lock;

void *ProcessA(void *arg)
{
    while(1){
        pthread_mutex_lock(&lock); 
        x = x + 1;
        if (x == 20) 
            x = 0;
        printf("ProcessA: %d\n", x);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *ProcessB(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("ProcessB: %d\n", x);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
int main()
{
    pthread_t threadA, threadB;
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Khoi tao Mutex that bai\n");
        return 1;
    }
    pthread_create(&threadA, NULL, ProcessA, NULL);
    pthread_create(&threadB, NULL, ProcessB, NULL);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_mutex_destroy(&lock);
    
    return 0;
}