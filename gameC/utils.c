/** @file utils.c
 *  @brief Various utility functions
 *
 *  This contains the music track signaler,
 *  the news print function and the close
 *  utility.
 *
 *  @author Mattia Mascarello (MatMasIt)
 *  @bug No known bugs.
 */
#include <stdio.h>
/**
       * @brief  Send a music command 
       * @param name music file to play
       * @return None
*/
void musicTrack(char *name)
{
    printf("mu|%s|um", name);
}
/**
       * @brief  Print News from `log.txt`
       * @return None
*/
void print_news()
{
    FILE *f;
    char c;
    f = fopen("log.txt", "r");
    c = fgetc(f);
    printf("\n------\n");
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(f);
    }

    fclose(f);
    printf("\n------\n");
}
/**
       * @brief  Close connection and send `CLOSE` verb
       * @return None
*/
void closeG()
{
    printf("\nCLOSE\n");
    exit(0);
}