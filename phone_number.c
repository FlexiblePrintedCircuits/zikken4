#include <stdio.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[]) {
char *regex = "^(070|080|090)-[0-9]{4}-[0-9]{4}$";
    regex_t preg;
    regmatch_t pm[2];
    char text[1026];
    FILE *fp;

    char t[24];

    if (regcomp(&preg, regex, REG_EXTENDED|REG_NEWLINE) != 0) {
        printf("regex is not available.\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    fscanf(fp, "%s", text);
    fclose(fp);

    int size = sizeof(pm) / sizeof(regmatch_t);
    int counter = 0;

    for (int i=0; i<strlen(text); i++) {
        strncpy(t, text+i, 13);
        if (regexec(&preg, t, size, pm, 0) == 0) {
            printf("%s\n", t);
            counter++;
        }
    }

    if (counter == 0) {
        puts("マッチする電話番号はありませんでした。");
    }

    regfree(&preg);
    return 0;
}