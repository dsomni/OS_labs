#include <stdio.h>
#include<pthread.h>

void myThread(){
    printf("I am in!\n");
}

int main(){
    pthread _t = thread;
    if (pthread_create(&thread, NULL, myThread, (void*)(intptr_t)i)){
        printf(" >>ERROR IN CREATING Thread %d!\n", i);
        pthread_exit(NULL);
        return 1;
    }else{
        printf(" >>Thread #%d created!\n", i);
    }
}
