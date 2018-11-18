#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define DELAY 1000000

int common;

/* this function is run by the second thread */
void *thread2(void *x_void_ptr)
{
    int i,j;
    int e = 0;

    while (e == 0)
    {
        if (common == -1)
            break;

        i = rand();

//        printf("%d ",i);
        common = i;

        for (j = 0; j < DELAY; j++)
            ;

        if (i != common)
        {
            printf("%d %d\n",i,common);
            printf("errore!thread terminato\n");
            common = -1;
            break;
        }
    }

    return NULL;
}

int main()
{

    int nRes;
    int par;
    /* this variable is our reference to the second thread */
    pthread_t t1,t2,t3;

    nRes =  pthread_create(&t1, NULL, thread2, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error creating thread 1\n");

        return 1;
    }
    nRes =  pthread_create(&t2, NULL, thread2, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error creating thread 2\n");

        return 1;
    }
    nRes =  pthread_create(&t3, NULL, thread2, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error creating thread 3\n");

        return 1;
    }

    nRes = pthread_join(t1, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error joining thread 1\n");

        return 2;
    }

    nRes = pthread_join(t2, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error joining thread 2\n");

        return 3;
    }

    nRes = pthread_join(t3, NULL);

    if(nRes != 0)
    {
        fprintf(stderr, "Error joining thread 3\n");

        return 4;
    }

    return 0;
}
