#include <string.h>
#include <stdio.h>
#include "gamedata.c"
#include "playerdata.c"
#include "graphics.c"
#include "utils.c"
#include <stdlib.h>
#include "menuchoices.c"

UserSave us;

int intentLauncher()
{
    char action[10];
    char email[40];
    char username[50];
    char password[20];
    scanf("%[^|]|%[^|]|%[^|]|%[^\n]", action, email, username, password);
    //printf("Action: %s\nEmail: %s\nUsername:%s\nPassword:%s\n", action, email, username, password);
    User u;
    if (strcmp(action, "signin") == 0)
    {
        u = login(&us, email, password);
        if (u.empty)
        {
            printf("Login error");
            closeG();
        }
        else
        {
            printf("\n<Welcome, %s>\n", u.username);
            main_menu_graph();
        }
    }
    else
    {
        printf("Signing up");
    }
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
    switch (ch - 1)
    {
    case LOCALPLAY:
        printf("::Local Play::");
        musicTrack("amacord");
        savegame_menu_graph(u);
        scanf("%d");
        break;
    case READNEWS:
        print_news();
        break;
    case 5:
        closeG();
        break;
    }
}
int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF, 0);
    us = loadList();
    logo();
    intentLauncher();
    closeG();
}