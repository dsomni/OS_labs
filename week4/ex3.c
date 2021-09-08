#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char REDIRECT_PATH[] = " > ex3.txt";

int main()
{
    printf("To quit write q\n\n\n");
    char user_input[255];
    char s[255];
    char ans[255];
    FILE *f;
    while (1)
    {

        scanf("%s", user_input);
        if (!strcmp(user_input, "q"))
        {
            return 0;
        }
        strcat(user_input, REDIRECT_PATH);
        int res = system(user_input);
        if (res == 1)
        {
            return 1;
        }

        f = fopen("ex3.txt", "r");
        ans[0] = '\0';
        while (1)
        {
            if (fgets(s, sizeof(s), f) == NULL)
            {
                break;
            }
            strcat(ans, s);
        }
        printf("\n%s\n", ans);
    }
    return 0;
}