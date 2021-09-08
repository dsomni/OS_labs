#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char CMD_PATH[255] = "/bin/\0";

int main()
{
    printf("To quit write q\n\n\n");

    char user_input[255];
    char s[255];
    int pid;
    while (1)
    {
        gets(user_input);
        if (!strcmp(user_input, "q"))
        {
            return 0;
        }

        pid = fork();
        if (pid == 0)
        {
            // child process (background)
            char *argv[255];
            char *word;
            int i = 0;
            int j;
            int p = 0;
            while (1)
            {
                word = (char *)malloc(sizeof(char) * 255);
                if (user_input[i] == '\0' || user_input[i] == '\n')
                {
                    break;
                }
                j = 0;
                while (user_input[i] != ' ' && user_input[i] != '\0' && user_input[i] != '\n')
                {
                    word[j] = user_input[i];
                    i++;
                    j++;
                }
                word[j] = '\0';
                argv[p] = word;
                p += 1;
                if (user_input[i] == '\0' || user_input[i] == '\n')
                {
                    break;
                }
                i++;
            }
            argv[p] = NULL;
            char prefix[255];
            strcpy(prefix, CMD_PATH);
            strcat(prefix, argv[0]);
            execve(prefix, argv, NULL);

            for (int y = 0; y < p; y++)
            {
                free(argv[y]);
            }

            return 0;
        }
    }
    return 0;
}