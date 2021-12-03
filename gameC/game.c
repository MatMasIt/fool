#include <string.h>
#include <stdio.h>
int main()
{
    setvbuf(stdout, NULL, _IONBF, 0); 
    char player[10];
    FILE *f;
    f = fopen("a.txt", "a");
    while (1)
    {
        scanf("%s", player);
        fprintf(f, "%s \n", player);
        printf("Pazzo stupido matto mattone %s\n", player);
    }
    fclose(f);
}