#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

#define DELAY 10000000

/* this function is run by the second thread */
void *thread2(void *x_void_ptr)
{
    int i,j;

    for (i = 0; i < 100; i++)
    {
        printf("abcdefghijklmnopqrstuvwxyz\n");
        for (j = 0; j < DELAY; j++)
            ;
    }

    /* the function must return something - NULL will do */
    return NULL;
}

int main()
{

    int i,j;
    int nRes;
    /* this variable is our reference to the second thread */
    pthread_t secondthread;

    /* create a second thread which executes inc_x(&x) */
    nRes =  pthread_create(&secondthread, NULL, thread2, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error creating thread\n");

        return 1;
    }

    for (i = 0; i < 100; i++)
    {
        printf("0123456789\n");
        for (j = 0; j < DELAY; j++)
            ;
    }

    /* wait for the second thread to finish */
    nRes = pthread_join(secondthread, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error joining thread\n");

        return 2;
    }

    return 0;
}
