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
        }
    }
    else
    {
        printf("Signing up\n");
        u = signup(&us, email, username, password);
        if (u.empty)
        {
            printf("Signup error");
            closeG();
        }
    }
    int ch = 0;
    FILE *fp;
    GameFile gf;
    if ((fp = fopen("./gameC/gamefile.obj", "rb")) == NULL)
    {
        printf("Could not open file");
        exit(1);
    }

    fread(&gf, sizeof(gf), 1, fp);
    fclose(fp);
    int mainLoopOn = 1;
    while (mainLoopOn)
    {
        main_menu_graph();
        ch = choicher(1, 5);
        switch (ch - 1)
        {
        case PLAY:
            printf("::Play::");
            int c;
            do
            {

                musicTrack("amacord");
                savegame_menu_graph(u);
                c = choicher(0, 3);
                if (c == 0)
                    break;
                if (c > u.saveslotsN)
                {
                    setSaveFile(gf, &u, c - 1);
                }
                else
                {
                    gameLoop(u, gf, c - 1);
                }
            } while (1);
            break;

        case CREDITS:
            printf("\n(C) 2021, Mattia Mascarello & Giacomo Roggero\n");
            break;
        case NEWS:
            print_news();
            break;
        case LOGOUT:
            printf("LOGOUT");
            exit(0);
            break;
        case DELETE:
            printf("Are you sure? [0/1]");
            int dc = choicher(0, 1);
            if (dc)
            {
                deleteUser(u);
                printf("\nOK!\n");
                printf("LOGOUT");
                exit(0);
            }
            break;
        }
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