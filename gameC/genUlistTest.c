/**
 * @file genUlistTest.c
 * @brief Generate sample user list with one user
 * @author Mattia Mascarello (MatMasIt)
 * @version 1.0
 * @date 2021-12-21
 *
 * @copyright MIT LICENSE 2021
 * 
 */
#include "utils.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "playerdata.c"
/**
 * @brief main generator function
 * 
 * @return int 
 */
int main()
{
    FILE *f;                                         // file pointer
    UserSave us;                                     // usersave list
    User u;                                          // user
    u.creationTime = time(NULL);                     // creation time to current time
    u.empty = 0;                                     //not empty
    u.initialized = 1;                               // initialized
    strcpy(u.password, "test");                      //set password to test password
    u.token = 1010;                                  // test token
    strcpy(u.username, "mattia");                    // test username
    strcpy(u.email, "m2.mascarello@liceococito.it"); // test Email
    u.saveslotsN = 1;                                // one saveslot
    SaveSlot s;                                      // saveslot struct
    s.worldID = 1;                                   // world 1
    s.roomID = 1;                                    // room 1
    s.itemsL = 1;                                    // one item
    s.lastUsed = time(NULL);                         // saveslot marked as fresh
    strcpy(s.slotName, "A good world");              // naming savestlot
    ItemSave is;                                     // initializing itemsave struct
    is.ID = 1;                                       // item id is 1
    is.quantity = 1;                                 // quantity is 1
    s.items[0] = is;                                 // setting item
    u.saveslots[0] = s;                              // setting saveslot
    u.saveslotsN = 1;                                // setting saveslots no to 1
    us.userN = 1;                                    // setting users no to 1
    us.userList[0] = u;                              // setting the user in the array
    f = fopen("./gameC/ulist.obj", "wb+");           //opening the file in write binrary mode
    if (f == NULL)
        us.userN = 0;
    fwrite(&us, sizeof(UserSave), 1, f); //saving
    fclose(f);
}