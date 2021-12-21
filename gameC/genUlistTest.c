#include "utils.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "playerdata.c"
int main()
{
    FILE *f;
    UserSave us;
    User u;
    u.creationTime = time(NULL);
    u.empty = 0;
    u.initialized = 1;
    strcpy(u.password, "test");
    u.token = 1010;
    strcpy(u.username, "mattia");
    strcpy(u.email, "m2.mascarello@liceococito.it");
    u.saveslotsN = 1;
    SaveSlot s;
    s.worldID = 1;
    s.roomID = 1;
    s.itemsL = 1;
    s.lastUsed = time(NULL);
    stpcpy(s.slotName, "A test slot");
    strcpy(s.slotName, "A good world");
    ItemSave is;
    is.ID = 1;
    is.quantity = 1;
    s.items[0] = is;
    u.saveslots[0] = s;
    u.saveslotsN = 1;
    us.userN = 1;
    us.userList[0] = u;
    f = fopen("./gameC/ulist.obj", "wb+");
    if (f == NULL)
        us.userN = 0;
    fwrite(&us, sizeof(UserSave), 1, f);
    fclose(f);
}