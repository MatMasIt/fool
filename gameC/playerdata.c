#include <unistd.h>
#include <stdio.h>
typedef struct ItemSave
{
    int ID;
    int quantity;

} ItemSave;

typedef struct SaveSlot
{
    int worldID;
    int roomID;
    char slotName[10];
    ItemSave items[10];
    int itemsL;
} SaveSlot;

typedef struct SaveFile
{
    char username[30];
    char email[50];
    SaveSlot saveslots[3];
    int saveslotsN;
    int initialized;

} SaveFile;

SaveFile loadSaveFile(char *uid)
{
    char filepath[100];
    FILE *fp;
    strcat(filepath, "playerfiles/");
    strcat(filepath, uid);
    strcat(filepath, ".obj");
    SaveFile s;
    s.initialized = 0;
    if (access(filepath, F_OK) == 0)
    {
        if ((fp = fopen(uid, "rb")) == NULL)
        {
            return s;
        }
        fread(&s, sizeof(SaveFile), 1, fp);
        return s;
    }
    else
    {
        return s;
    }
}