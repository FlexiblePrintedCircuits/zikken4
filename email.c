#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char str[256];

    int i;

    const char *regex = "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+";
    regex_t preg;
    char str1[20];
    regmatch_t pm[1];

    if(regcomp(&preg, regex, REG_EXTENDED|REG_NEWLINE) != 0){
        printf("regex is not available.\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("%s File Not Found\n", argv[1]);
        return -1;
    }

    while(fgets(str, 256, fp) != NULL){
        if(regexec(&preg, str, 1, pm, 0) == 0){
            i=0;
            while(str[i]!='\0') {
                if(str[i]>='a' && str[i]<='z') {
                    printf("%c",str[i]);
                } else if(str[i] == '.') {
                    printf("%c",str[i]);
                } else if(str[i] == '@') {
                    printf("%c",str[i]);
                }
                i++;
            }
            printf("\n");
        }
    }
    fclose(fp);

    regfree(&preg);
    return 0;
}