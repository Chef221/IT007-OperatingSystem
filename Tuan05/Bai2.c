#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h> 
#include <time.h>
#define N 100 
int a[N];
int count = 0;
sem_t sem;

// --- Thread 1: Producer ---
void* Producer(void* arg) {
    while(1) {
        int num = rand() % 100 + 1;
        sem_wait(&sem);
        if (count < N) {
            a[count] = num;
            count++;
            printf("[Producer] Them %d. So phan tu: %d\n", num, count);
        } else {
            printf("[Producer] Mang day (Full).\n");
        }
        sem_post(&sem);
        sleep(1); 
    }
    return NULL;
}

void* Consumer(void* arg) {
    while(1) {
        sem_wait(&sem);
        if (count > 0) {
            int val = a[count - 1];
            count--; 
            printf("[Consumer] Lay %d. So phan tu: %d\n", val, count);
        } else {
            printf("Nothing in array a\n");
        }
        sem_post(&sem);
        sleep(2); 
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    srand(time(NULL));
    sem_init(&sem, 0, 1);
    pthread_create(&t1, NULL, Producer, NULL);
    pthread_create(&t2, NULL, Consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem);

    return 0;
}