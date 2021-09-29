#include <stdlib.h>
#include <stdio.h>

int main()
{
    // array of 255 strings with length 255 chars each
    char **s =  (char **)malloc(sizeof((char *)malloc(sizeof(char)*255))*255); // the same as: char* s[255];
    char foo[] = "Hello World";
    *s = foo;
    printf("s is %d\n", s);
    s[0] = foo;
    printf("s[0] is %s\n", s[0]);
    return (0);
}