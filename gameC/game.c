#include <string.h>
#include <stdio.h>
#include "playerdata.c"
#include "graphics.c"
#include <stdlib.h>
UserSave us;
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
int main_menu_choice()
{
    char action[10];
    char email[40];
    char username[50];
    char password[20];
    scanf("%[^|]|%[^|]|%[^|]|%[^\n]", action, email, username, password);
    printf("Action: %s\nEmail: %s\nUsername:%s\nPassword:%s\n", action, email, username, password);
    User u;
    if (strcmp(action, "signin")==0)
    {
        u = login(&us, email, password);
        if (u.empty)
        {
            printf("Login error");
            exit(0);
        }
        else
        {
            printf("Welcome, %s", u.username);
        }
    }
    else
    {
        printf("Signing up");
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
        exit(0);
        break;
    }
}
int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF, 0);
    us = loadList();
    logo();
    main_menu_graph();
    main_menu_choice();
}