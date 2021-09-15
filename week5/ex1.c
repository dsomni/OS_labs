#include <stdio.h>
#include <pthread.h>

#define N 10

int want[N];
int turn[N];

void lock_init()
{
    for (int i = 0; i < N; i++)
    {
        want[i] = 0;
        turn[i] = 0;
    }
}

void lock(int current)
{
    for (int level = 0; level < N-1; level++){
        want[current] = level + 1;
        turn[level] = current;

        while(1){
            int found = 0;
            for (int thread = 0; !found && thread < N; thread++){
                if (thread == current) continue;
                if (want[thread] > level){
                    found = 1;
                }
            }
            if (!found) break;
            if (turn[level] != current) break;
        }
    }
}


void unlock(int current)
{
    want[current] = 0;
}

void *myThread(void *i)
{
    int current = (int *)i;
    lock(current);

    printf("Hello from myThread #%d!\n", current);

    unlock(current);

    pthread_exit(NULL);
}

int main()
{

    for (int i = 0; i < N; i++)
    {
        pthread_t thread;
        if (pthread_create(&thread, NULL, myThread, (void *)i))
        {
            printf(" >>ERROR IN CREATING Thread %d!\n", i);
            return 1;
        }
        else
        {
            printf(" >>Thread #%d created!\n", i);
        }
    }
}
