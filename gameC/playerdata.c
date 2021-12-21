/**
 * @file playerdata.c
 * @author Mattia Mascarello (MatMasIt)
 * @brief Contains player data structures and related functions
 * Contains player data structures and functions for handling
 * login, signup, deletion, etc
 * @version 1.0
 * @date 2021-12-21
 *
 * @copyright MIT LICENSE 2021
 * 
 */
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
typedef enum authErrors
{
    E_EMAILUSED,
    E_USERUSED,
    E_TOKENERR
} authError;

#define TOKEN int
typedef struct ItemSave
{
    int ID;
    int quantity;

} ItemSave;

typedef struct SaveSlot
{
    int lastUsed;
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
User login(UserSave *us, char *email, char *password)
{
    User u;
    for (int i = 0; i < (*us).userN; i++)
    {
        if (strcmp((*us).userList[i].email, email) == 0 && strcmp((*us).userList[i].password, password) == 0)
        {
            u = (*us).userList[i];
            u.token = newToken(us, i);
            (*us).userList[i] = u;
            saveList(*us);
            return u;
        }
    }
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
    for (int i = 0; i < (*us).userN; i++)
    {
        if (strcmp(email, (*us).userList[i].email) == 0)
        {
            printf("\nEmail is already used\nLOGOUT");
            closeG();
        }
        if (strcmp(username, (*us).userList[i].username))
        {

            printf("\nUsername is already used\nLOGOUT");
            closeG();
        }
    }
    strcpy(u.email, email);
    strcpy(u.username, username);
    strcpy(u.password, password);
    u.empty = 0;
    u.initialized = 1;
    u.creationTime = time(NULL);
    (*us).userN++;
    (*us).userList[(*us).userN - 1] = u;
    saveList((*us));
    return u;
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

void saveUser(User u)
{
    UserSave us = loadList();
    for (int i = 0; i < us.userN; i++)
    {
        if (us.userList[i].token == u.token)
            us.userList[i] = u;
    }
    saveList(us);
}

void deleteUser(User u)
{
    UserSave us = loadList();
    for (int i = 0; i < us.userN; i++)
    {
        if (us.userList[i].token == u.token)
        {
            us.userList[i] = us.userList[us.userN - 1];
            us.userN--;
        }
    }
    saveList(us);
}