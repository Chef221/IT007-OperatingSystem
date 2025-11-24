#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

int main(int argc, char *argv[])
{
    struct timeval start, end;
    double timetaken;
    if (argc != 2)
    {
        fprintf(stderr, "Su dung: ./time <command>\n");
        exit(1);
    }
    gettimeofday(&start, NULL);
    system(argv[1]);
    gettimeofday(&end, NULL);
    timetaken = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Thoi gian thuc thi: %.4f\n", timetaken);
    return 0;
}