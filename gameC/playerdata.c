#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define E_EMAILUSED 0
#define E_USERUSER 1
#define E_TOKENERR 0
#define TOKEN int
typedef struct ItemSave
{
    int ID;
    int quantity;

} ItemSave;

typedef struct SaveSlot
{
    int worldID;
    int roomID;
    char slotName[20];
    ItemSave items[10];
    int itemsL;
} SaveSlot;

typedef struct User
{
    char username[30];
    char email[50];
    char password[50];
    SaveSlot saveslots[3];
    int saveslotsN;
    int initialized;
    int token;
    int empty;
    int creationTime;
} User;

typedef struct UserSave
{
    User userList[100];
    int userN;
} UserSave;

UserSave loadList()
{
    FILE *f;
    UserSave us;
    f = fopen("./gameC/ulist.obj", "rb");
    if (f == NULL)
        us.userN = 0;
    fread(&us, sizeof(UserSave), 1, f);
    fclose(f);
    return us;
}

void saveList(UserSave us)
{
    FILE *f;
    f = fopen("./gameC/ulist.obj", "wb");
    fwrite(&us, sizeof(UserSave), 1, f);
    fclose(f);
}

User login(UserSave *us, char *email, char *password)
{
    //TODO make login work
    printf("KKKK%s-%s", email, password);
    for (int i = 0; i < (*us).userN; i++)
    {
        if (strcmp((*us).userList[i].email, email) == 0 && strcmp((*us).userList[i].password, password) == 0)
            return (*us).userList[i];
    }
    User u;
    u.empty = 1;
    return u;
}

User signup(UserSave *us, char *email, char *username, char *password)
{

    User u;
    if ((*us).userN > 100)
    {
        u.empty = 1;
        return u;
    }
    strcpy(u.email, email);
    strcpy(u.username, username);
    strcpy(u.password, password);
    u.empty = 0;
    u.initialized = 1;
    u.creationTime = time(NULL);
    (*us).userList[(*us).userN - 1] = u;
    (*us).userN++;
}

TOKEN newToken(UserSave *us, int index)
{

    srand(time(NULL)); // Initialization, should only be called once.
    int r, flag = 1;
    while (flag)
    {
        r = rand();
        flag = 0;
        for (int i = 0; i < (*us).userN; i++)
        {
            if ((*us).userList[i].token == r)
            {
                flag = 1;
                break;
            }
        }
    }
    (*us).userList[index].token = r;
    return r;
}

User getFromToken(UserSave us, TOKEN t)
{
    User u;
    for (int i = 0; i < us.userN; i++)
    {
        if (us.userList[i].token == t)
            return us.userList[i];
    }
    u.empty = 1;
    return u;
}

void saveFromToken(UserSave *us, User u)
{
    for (int i = 0; i < (*us).userN; i++)
    {
        if ((*us).userList[i].token == u.token)
            (*us).userList[i] = u;
    }
}
