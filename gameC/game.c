#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include "gamedata.c"
#include "playerdata.c"
#include "menuchoices.c"
#include "graphics.c"

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
    ch = choicher(1, 5);
    FILE *fp;
    GameFile gf;
    if ((fp = fopen("./gameC/gamefile.obj", "rb")) == NULL)
    {
        printf("Could not open file");
        exit(1);
    }

    fread(&gf, sizeof(gf), 1, fp);
    fclose(fp);
    switch (ch - 1)
    {
    case LOCALPLAY:
        printf("::Local Play::");
        musicTrack("amacord");
        int looping = 0;
        int c;
        do
        {
            savegame_menu_graph(u);
            c = choicher(1, 3);
            if (c > u.saveslotsN)
            {
                if (setSaveFile(gf, &u, c - 1))
                {
                    looping = 1;
                }
                else
                {
                    looping = 0;
                }
            }
            else
            {
                gameLoop(u, gf, c - 1);
            }
        } while (looping);
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