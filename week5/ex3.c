#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define DELAY_C 2
#define DELAY_P 2

pthread_cond_t flagC;
pthread_cond_t flagP;
pthread_mutex_t lock;
int buffer[BUFFER_SIZE];
int sent = 0;
int item = 0;

void producer(void *i)
{
    while (1)
    {

        if (sent == BUFFER_SIZE)
        {
            // printf("Wake Up Consumer\n");
            // pthread_cond_signal(&flagP);

            printf("Producer Is Sleep\n");
            pthread_cond_wait(&flagC, &lock);
            printf("Producer Is Awake\n");
        }

        item = (item + 1) % 1000;
        buffer[sent] = item;
        sent++;
        printf(" >> Produced Item: %d\n", item);

        if (sent == 1)
        {
            printf("Wake Up Consumer\n");
            pthread_cond_signal(&flagP);
        }

        sleep(DELAY_P);
    }
}

void consumer(void *i)
{
    while (1)
    {

        if (sent == 0)
        {
            // printf("Wake Up Producer\n");
            // pthread_cond_signal(&flagC);

            printf("Consumer Is Sleep\n");
            pthread_cond_wait(&flagP, &lock);
            printf("Consumer Is Awake\n");
        }

        sent--;
        printf(" >> Got Item: %d\n", buffer[sent]);

        if (sent == BUFFER_SIZE - 1)
        {
            printf("Wake Up Producer\n");
            pthread_cond_signal(&flagC);
        }

        sleep(DELAY_C);
    }
}

int main()
{
    pthread_t p, c;

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);

    return 0;
}
