#include <stdio.h>
#include <string.h>

int main(){
    char* s;
    size_t len = 0;

    printf("Enter a string:\n");
    getline(&s, &len, stdin);

    int l = strlen(s);
    char r_s[l];

    for (int i = 0; i < l; i++){
        r_s[i] = s[l-i-2];
    }
    r_s[l] = '\0';

    printf("Your string reversed:\n");
    printf("%s\n", r_s);
    return 0;
}