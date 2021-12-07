#include <string.h>
#include <stdio.h>
#include "playerdata.c"
#include "graphics.c"
#include <stdlib.h>
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
int main_menu_choice(char *uid)
{
    char *action;
    char *email;
    char *username;
    char *password;
    scanf("%s|%s|%s|%s", action, email, username, password);
    if (strcmp(action, "signin"))
    {
        
    }
    else
    {
    }
    scanf("%*s");
    int ch = 0;
    while (ch < 1 || ch > 5)
    {
        while (scanf("%d", &ch) != 1)
        {
            // Tell the user that the entry was invalid
            printf("??");
            // Asterisk * tells scanf to read and ignore the value
            scanf("%*s");
        }
        if (ch < 1 || ch > 5)
            printf("??");
    }
    switch (ch)
    {
    case 1:
        musicTrack("fi");
        break;
    case 3:
        print_news();
        break;
    case 5:
        exit(1);
        break;
    }
}
int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF, 0);
    logo();
    main_menu_graph();
    main_menu_choice(argv[0]);
}