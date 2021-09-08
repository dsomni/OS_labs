#include <stdio.h>
#include <sys/types.h>

int main()
{

    int n = 3;

    int pid = fork();

    if (pid > 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Hello from parent [%d - %d]\n", pid, i);
        }
    }
    else if (pid == 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Hello from child [%d - %d]\n", pid, i);
        }
    }
    else
    {
        return -1;
    }

    return 0;
}