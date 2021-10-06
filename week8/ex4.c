#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#define TEN_MB sizeof(int) * 256 * 1024 * 10

void printInfo(struct rusage *usage)
{
    printf("System CPU time used: %li\n", usage->ru_stime.tv_sec);
    printf("Maximum resident set size: %ld\n", usage->ru_maxrss);
    printf("Integral shared memory size: %ld\n", usage->ru_ixrss);
    printf("Integral unshared data size: %ld\n", usage->ru_idrss);
    printf("Integral unshared stack size: %ld\n", usage->ru_isrss);
    printf("\n");
}

int main()
{
    struct rusage usage;
    for (int i = 0; i < 10; i++)
    {
        void *p = malloc(TEN_MB);
        printf("###########################\n");
        printf("### 10MB was allocated! ###\n");
        printf("###########################\n");
        memset(p, 0, TEN_MB);
        getrusage(RUSAGE_SELF, &usage);
        printInfo(&usage);
        sleep(1);
    }

    return 0;
}