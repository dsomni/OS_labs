#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TEN_MB sizeof(int)*256*1024*10

int main()
{
    for (int i = 0; i < 10; i++)
    {
        void* p = malloc(TEN_MB);
        printf("10MB was allocated!\n");
        memset(p, 0, TEN_MB);
        sleep(1);
    }
    // when running ex3.sh we can see, that Virtual memory and Resources for process increas each time we allocate 10Mb
    // also swapping memory increases

    return 0;
}