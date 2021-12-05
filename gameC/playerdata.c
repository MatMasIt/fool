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
    SaveSlot saveslots[3];
    int saveslotsN;

} SaveFile;
