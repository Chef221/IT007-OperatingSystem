#include<stdio.h>
#include<pthread.h>
int x = 0;
void *ProcessA(void *arg)
{
    while(1){
        x = x + 1;
        if (x == 20) 
            x = 0;
        printf("ProcessA: %d\n",x);
    }
}
void *ProcessB(void *arg)
{
    while(1)
    {
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("ProcessB: %d\n",x);
    }
}
int main()
{
    pthread_t threadA, threadB;
    pthread_create(&threadA, NULL, ProcessA, NULL);
    pthread_create(&threadB, NULL, ProcessB, NULL);
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    return 0;
}