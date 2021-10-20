#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void scan_dir(char *dir)
{
    DIR *dp;
    struct dirent *file;
    struct stat buffer;

    if ((dp = opendir(dir)) == NULL)
    {
        printf("Error\n");
        return;
    }
    // printf();
    system("echo 'FILE -- HARD LINKS'");
    chdir(dir);
    while ((file = readdir(dp)) != NULL)
    {
        stat(file->d_name, &buffer);
        if (strcmp(".", file->d_name) == 0 ||
            strcmp("..", file->d_name) == 0)
            continue;
        if (buffer.st_nlink >= 2)
        {
            char *s = malloc(sizeof(char)*256);
            sprintf(s, "echo '%s --' | tr '\n' ' ' & find . -inum %ld | tr '\n' ' '", file->d_name, buffer.st_ino);
            system(s);
            system("echo");
        }
    }
    chdir("..");
}

int main()
{
    scan_dir("./tmp");
    return 0;
}