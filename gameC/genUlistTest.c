#include <stdio.h>
#include "playerdata.c"
int main()
{
    FILE *f;
    UserSave us;
    User u;
    u.creationTime = 0;
    u.empty = 0;
    u.initialized = 1;
    strcpy(u.password, "test");
    strcpy(u.token, "aaa");
    strcpy(u.username, "username");
    strcpy(u.email, "m2.mascarello@liceococito.it");
    u.saveslotsN=1;
    SaveSlot s;
    s.itemsL;
    u.saveslots=;
    us.userN = 1;
    us.userList
        f = fopen("ulist.obj", "rb+");
    if (f == NULL)
        us.userN = 0;
    fread(&us, sizeof(UserSave), 1, f);
    fclose(f);
}