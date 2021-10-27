#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include<string.h>

int main(int argc, char * argv[])
{
    // command line flag to determine whether
    // should change root or not
    // 1 - change root
    // 0 - dor not change
    if (argc==2 && strcmp(argv[1], "1")==0){
        chroot("./lofsdisk");
        printf("WITH CHROOT\n");
    }else{
        printf("WITHOUT CHROOT\n");
    }

    DIR *d;
    struct dirent *dir;
    d = opendir("/");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    printf("\n\n");
    return 0;
}