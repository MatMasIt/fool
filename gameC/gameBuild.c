/** @file gameBuild.c
 *  @brief Gamefile data builder
 *  Builds the gamefile
 *  @author Mattia Mascarello (MatMasIt)
 *  @version 1.0
 *  @date 2021-12-21
 *
 *  @copyright MIT LICENSE 2021
 */
#include "gamedata.c" //include gamefile structs and utils
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
/**
 * @brief Main
 * Builds the game file
 * 
 * @return int 
 */
int main()
{
  FILE *fp;       // file pointer to the new gamefile
  GameFile gf;    // gamefile object
  Item items[10]; //item list
  World w;        //world
  Room rooms[10]; //room list

  /**
     * * * * * * * * * * * * * * * * * * * * * * * * * 
     *                                               *
     *              Items instantiation              *
     *                                               *
     * * * * * * * * * * * * * * * * * * * * * * * * *
     */
  items[0].ID = 1;
  strcpy(items[0].name, "Giovanni Palestra");
  strcpy(items[0].desc, ">Effigy of famous wrestler Giovanni Palestra\nDrawings by mr. Adrian.");
  items[0].healtheffect = 10;

  items[1].ID = 2;
  strcpy(items[1].name, "Vincenzo Adamo");
  strcpy(items[1].desc, "Adamooooo");
  items[1].healtheffect = -10;

  items[2].ID = 3;
  strcpy(items[2].name, "Autograph by Di Pietro");
  strcpy(items[2].desc, "> Yes, that one");
  items[2].healtheffect = -10;

  items[3].ID = 4;
  strcpy(items[3].name, "Giulio Andreotti");
  strcpy(items[3].desc, "\n\"Change the world.... My final message\nGoodbye!\"\n");
  items[3].healtheffect = -10;

  /**
     * * * * * * * * * * * * * * * * * * * * * * * * * 
     *                                               *
     *      Rooms & Paths instantiation              *
     *                                               *
     * * * * * * * * * * * * * * * * * * * * * * * * *
     */
  Path p;

  p.dir = N;
  p.toRoomId = 2;

  rooms[0].ID = 1;
  strcpy(rooms[0].name, "Liceo cocito");
  strcpy(rooms[0].desc, "It has been teleported into mt. Vesuvius");
  strcpy(rooms[0].musicFile, "funiculi");
  rooms[0].items[0] = items[0]; // giovanni palestra
  rooms[0].itemsN = 1;
  rooms[0].paths[0] = p;

  p.dir = W;
  p.toRoomId = 3;

  rooms[0].paths[1] = p;
  rooms[0].pathsN = 2;

  p.dir = S;
  p.toRoomId = 1;

  rooms[1].ID = 2;
  strcpy(rooms[1].name, "Villa Arcore");
  strcpy(rooms[1].desc, "\"We bear big pride within us\"");
  strcpy(rooms[1].musicFile, "fi");
  rooms[1].items[0] = items[2]; // Di Pietro
  rooms[1].itemsN = 1;
  rooms[1].paths[0] = p;
  rooms[1].pathsN = 1;

  p.dir = E;
  p.toRoomId = 1;

  rooms[2].ID = 3;
  strcpy(rooms[2].name, "Casa di Sinodo");
  strcpy(rooms[2].desc, "The surgery room is occupied");
  strcpy(rooms[2].musicFile, "tarant");
  rooms[2].items[0] = items[1]; // vincenzo
  rooms[2].items[1] = items[3]; // andreotti
  rooms[2].itemsN = 1;
  rooms[2].paths[0] = p;
  rooms[2].pathsN = 1;

  w.ID = 1;
  strcpy(w.name, "Testlandia");
  strcpy(w.desc, "Uh, a test world");
  w.rooms[0] = rooms[0];
  w.rooms[1] = rooms[1];
  w.rooms[2] = rooms[2];
  w.roomsN = 3;

  gf.uid = 1;
  gf.worldsN = 1;
  gf.worlds[0] = w;
  gf.creationTime = time(NULL);                           // set gamefile creation time
  if ((fp = fopen("./gameC/gamefile.obj", "wb")) == NULL) // get gamefile pointer
  {
    printf("Could noy open file");
    exit(0);
  }

  fwrite(&gf, sizeof(gf), 1, fp); // write to gamefile
  fclose(fp);

  /*
                Map


                        Arcore
                          |
                Sinodi - Cocito
*/
}
