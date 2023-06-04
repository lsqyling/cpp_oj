#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


static void *func(void *argv)
{
    pthread_t tid, *id;
    id = argv;
    tid = pthread_self();
    printf("thread-%d: func is working!", pthread_equal(tid, *id));
    pthread_exit(NULL);
//    return NULL;
}



int main()
{
    pthread_t tid;
    int err;

    puts("Begin!");
    err = pthread_create(&tid, NULL, func, &tid);
    if (err)
    {
        fprintf(stderr, "pthread_create():%s", strerror(err));
        exit(1);
    }

    pthread_join(tid, NULL);
    puts("End!");


    exit(0);
}
