#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <string.h>

#define LEFT            30000000
#define RIGHT           30000200
#define THR_NUM         (RIGHT-LEFT+1)

static int is_prime(int n)
{
    if (n < 2)
        return 0;
    int sqrt_n = sqrt(n);
    for (int i = 2; i <= sqrt_n; ++i)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

static void *thr_func(void *argv)
{
    int n = *(int *)argv;
    if (is_prime(n))
        printf("%d is a primer.\n", n);
    pthread_exit(NULL);
}




int main()
{
    pthread_t tid[THR_NUM];
    int err;

    for (int i = LEFT; i <= RIGHT; ++i)
    {
        err = pthread_create(tid + i - LEFT, NULL, thr_func, &i);
        if (err)
        {
            fprintf(stderr, "pthread_create():%s\n", strerror(err));
            exit(1);
        }
    }
    for (int i = 0; i < THR_NUM; ++i)
    {
        pthread_join(tid[i], NULL);
    }

    exit(0);
}



