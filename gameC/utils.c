
#include <stdio.h>
void musicTrack(char *name)
{
    printf("mu|%s|um", name);
}
void print_news()
{
    FILE *f;
    char c;
    f = fopen("log.txt", "r");
    c = fgetc(f);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(f);
    }

    fclose(f);
}
void closeG(){
    printf("\nCLOSE\n");
    exit(0);
}