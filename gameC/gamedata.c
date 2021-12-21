/** @file gamedata.c
 *  @brief Game data structures and related functions
 *  This contains game data structs and associated
 *  manipulation, querying and loading facilities
 *
 *  @author Mattia Mascarello (MatMasIt)
 *  @version 1.0
 *  @date 2021-12-21
 *
 * @copyright MIT LICENSE 2021
 */

//to be used in paths
#define N 0
#define S 1
#define E 2
#define W 3
// custom direction type alias
#define direction int
/**
 * @brief Item struct
 * holds item data
 */
typedef struct Item
{
    int ID;
    char name[50];
    char desc[100];
    int healtheffect;

} Item;
/**
 * @brief Path struct
 * holds path direction and destination
 */
typedef struct Path
{
    direction dir; //0 1 2 3 n s e w
    int toRoomId;

} Path;
/**
 * @brief Room struct
 * holds room data, paths and items within it
 */
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

/**
 * @brief World struct
 * holds world data, rooms within it
 */
typedef struct World
{
    int ID;
    char name[20];
    char desc[100];
    Room rooms[20]; //player lands in room 1
    int roomsN;

} World;
/**
 * @brief GameFile strutct
 * a collection of worlds
 */
typedef struct GameFile
{
    int uid;
    int creationTime;
    World worlds[10];
    int worldsN;

} GameFile;
/**
 * @brief Get the World object by its ID
 *
 * @param f GameFile object
 * @see GameFile
 * @param ID World id
 * @return World 
 */
World getWorldById(GameFile f, int ID)
{
    for (int i = 0; i < f.worldsN; i++)
    {
        if (f.worlds[i].ID == ID)
            return f.worlds[i];
    }
}
/**
 * @brief Get the Room object by its ID
 * 
 * @param w World object
 * @param ID Room id
 * @return Room 
 */
Room getRoom(World w, int ID)
{
    for (int i = 0; i < w.roomsN; i++)
    {
        if (w.rooms[i].ID == ID)
            return w.rooms[i];
    }
}
/**
 * @brief Get the Item objecy By its ID
 * 
 * @param w World object
 * @param ID Item ID
 * @return Item 
 */
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