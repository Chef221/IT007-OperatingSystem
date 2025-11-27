#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int sells, products;
int MSSV = 1190; //24521190
sem_t sem;

void* Sells(void *arg)
{
    while(sells <= products)
    {
        sem_wait(&sem);
        sells++;
        printf("Sells: %d\n", sells);
    }
    return NULL;
}
void *Products(void *arg)
{
    while(products <= sells + MSSV)
    {
        products++;
        printf("Products: %d\n", products);
        sem_post(&sem);
    }
    return NULL;
}
int main()
{
    pthread_t t1, t2;
    sells = 0;
    products = 0;
    sem_init(&sem, 0, 0);
    pthread_create(&t1, NULL, Sells, NULL);
    pthread_create(&t2, NULL, Products, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&sem);
    return 0;
}