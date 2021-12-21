/** @file game.c
 *  @brief Main game file
 *  This contains the main game loop
 *
 *  @author Mattia Mascarello (MatMasIt)
 *  @version 1.0
 *  @date 2021-12-21
 *
 *  @copyright MIT LICENSE 2021
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.c"
#include "gamedata.c"
#include "playerdata.c"
#include "menuchoices.c"
#include "graphics.c"

UserSave us; // List of users

/**
 * @brief Launch main game getting the intent from stdin
 * Essentially the game's main
 * 
 * @return int 
 */
int intentLauncher()
{
    char action[10];                                                      // signup or signin
    char email[40];                                                       // user's email
    char username[50];                                                    // username
    char password[20];                                                    // password
    scanf("%[^|]|%[^|]|%[^|]|%[^\n]", action, email, username, password); // The first thing sent in the websocket is a formatted string with the parameters
    User u;                                                               // user object
    if (strcmp(action, "signin") == 0)                                    // action is signin
    {
        u = login(&us, email, password); // try to login with provided credentials and assign user object
        if (u.empty)                     // check if login failed
        {
            printf("Login error"); // display login error
            closeG();              // close game
        }
        else
        {
            printf("\n<Welcome, %s>\n", u.username); // welcome user
        }
    }
    else
    {
        printf("Signing up\n");                     // Sign up process start
        u = signup(&us, email, username, password); //  signup and assign user object
        if (u.empty)                                // check for success
        {
            printf("Signup error"); // display error
            closeG();               // quit game
        }
    }
    int ch = 0;                                             // choice variable
    FILE *fp;                                               // gamefile file pointer
    GameFile gf;                                            // gamefile object
    if ((fp = fopen("./gameC/gamefile.obj", "rb")) == NULL) // open the gamefile object
    {
        printf("Could not open file"); // Error if cannot open
        exit(1);                       // quit
    }

    fread(&gf, sizeof(gf), 1, fp); // read gamefile object from file
    fclose(fp);                    // close stream
    int mainLoopOn = 1;            // main loop flag on
    while (mainLoopOn)             // main loop
    {
        main_menu_graph();   // main menu graphical
        ch = choicher(1, 5); // choose option
        switch (ch - 1)      //go to chosen section
        {
        case PLAY:              // play
            printf("::Play::"); // display play banner
            int c;              // choice variable
            do
            {
                musicTrack("amacord");  // play soundtrack
                savegame_menu_graph(u); // display savegame choice menu
                c = choicher(0, 3);     // choose savefile
                if (c == 0)             //quit on 0
                    break;
                if (c > u.saveslotsN) // new savefile creation
                {
                    setSaveFile(gf, &u, c - 1); //call savefile setter
                }
                else
                {
                    gameLoop(u, gf, c - 1); // proceed to game loop with selected gamefile
                }
            } while (1); // iterate continuosly
            break;

        case CREDITS: // credits
            printf("\n(C) 2021, Mattia Mascarello & Giacomo Roggero\n");
            break;
        case NEWS:        // news section
            print_news(); // news printer
            break;
        case LOGOUT:          // logout
            printf("LOGOUT"); // print logout
            exit(0);
            break;
        case DELETE:
            printf("Are you sure? [0/1]"); // The user must be sure to delete
            int dc = choicher(0, 1);       //confirm
            if (dc)
            {
                deleteUser(u); //delete user
                printf("\nOK!\n");
                printf("LOGOUT"); //logout signal
                exit(0);
            }
            break;
        }
    }
}
/**
 * @brief Game actual Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{

    setvbuf(stdout, NULL, _IONBF, 0); // no buffering, allows node websocket
    us = loadList();                  // load user list
    logo();                           // logo
    intentLauncher();                 // game main
    closeG();                         // fallback close
}
/**
 * You awake one day with a sense of dread, at first pinning it on the common annoyances of work, unaware of the descent you will experience over the next few months. 
 * The sleepless nights, the lack of joy, the inability to communicate your feelings to the seemingly happy and content figures that surround you. 
 * A rift develops between your former and present self. 
 * Hobbies no longer satisfy your desire for weekend escapism. 
 * Your loved ones notice peculiar behaviours but, unlike missing an arm, the symptoms aren’t noticeable enough to warrant a concern. 
 * And of course you wouldn’t want to bring them down.
 * Talking about it only makes it real.
 * Every now and then you feel elated, overjoyed with life and almost godlike.
 * Your mania further drives away and confuses the only ones willing to listen.
 * In twilight moments of self-reflection you see the totality of anguish.
 * Your x-ray vision of despair lasers through the impermanence of it all, the insistent misery of being;
 * your only sense of comfort, of stability, is your acknowledgment that there truly is nothing to be hopeful for.
 * Make no mistake about people who leap from burning windows. 
 * Their terror of falling from a great height is still just as great as it would be for you or me standing speculatively at the same window just checking out the view; i.e. the fear of falling remains a constant. 
 * The variable here is the other terror, the fire’s flames: when the flames get close enough, falling to death becomes the slightly less terrible of two terrors. 
 * It’s not desiring the fall; it’s terror of the flames.
 */