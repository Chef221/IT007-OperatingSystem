#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0, in = 0, out = 0;
int total_sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE)
            pthread_cond_wait(&empty, &mutex);

        int value = rand() % 10 + 1;
        buffer[in] = value;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        total_sum += value;

        printf("Produced: %d (Total sum = %d)\n", value, total_sum);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);

        if (total_sum > 100)
            break;

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (count == 0 && total_sum <= 100)
            pthread_cond_wait(&full, &mutex);

        if (total_sum > 100 && count == 0)
        {
            pthread_mutex_unlock(&mutex);
            break;
        }

        int value = buffer[out];
        printf("Consumed: %d\n", value);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    printf("Final total sum = %d\n", total_sum);
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
