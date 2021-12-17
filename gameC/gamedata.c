#define N 0
#define S 1
#define E 2
#define W 3
#define direction int
typedef struct Item
{
    int ID;
    char name[50];
    char desc[100];
    int healtheffect;

} Item;

typedef struct Path
{
    direction dir; //0 1 2 3 n s e w
    int toRoomId;

} Path;

typedef struct Room
{
    int ID;
    char name[20];
    char desc[100];
    char musicFile[20];
    Path paths[10];
    int pathsN;
    Item items[10];
    int itemsN;

} Room;

typedef struct World
{
    int ID;
    char name[20];
    char desc[100];
    Room rooms[20]; //player lands in room 1
    int roomsN;

} World;

typedef struct GameFile
{
    int uid;
    int creationTime;
    World worlds[10];
    int worldsN;

} GameFile;

World getWorldById(GameFile f, int ID)
{
    for (int i = 0; i < f.worldsN; i++)
    {
        if (f.worlds[i].ID == ID)
            return f.worlds[i];
    }
}

Room getRoom(World w, int ID)
{
    for (int i = 0; i < w.roomsN; i++)
    {
        if (w.rooms[i].ID == ID)
            return w.rooms[i];
    }
}

Item getItemById(World w, int ID)
{
    for (int i = 0; i < w.roomsN; i++)
    {
        for (int j = 0; j < w.rooms[i].itemsN; i++)
        {
            if (w.rooms[i].items[j].ID == ID)
                return w.rooms[i].items[j];
        }
    }
}