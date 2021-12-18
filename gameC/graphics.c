int prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void logo()
{
    printf("  █████▒▒█████   ▒█████   ██▓    \n");
    printf("▓██   ▒▒██▒  ██▒▒██▒  ██▒▓██▒    \n");
    printf("▒████ ░▒██░  ██▒▒██░  ██▒▒██░    \n");
    printf("░▓█▒  ░▒██   ██░▒██   ██░▒██░    \n");
    printf("░▒█░   ░ ████▓▒░░ ████▓▒░░██████▒\n");
    printf("Mattia Mascarello, Giacomo Roggero \n             v. 1.0 \n 2021   \n");
}
int main_menu_graph()
{
    printf("╔═══════════════════════════╗\n");
    printf("║        Main Menu             ║\n");
    printf("╠════════╦══════════════════╣\n");
    printf("║ Option  ║      Action        ║\n");
    printf("╠════════╬══════════════════╣\n");
    printf("║      1  ║ Play               ║\n");
    printf("║      2  ║ Credits            ║\n");
    printf("║      3  ║ Read recent news   ║\n");
    printf("║      4  ║ Logout             ║\n");
    printf("║      5  ║ Delete             ║\n");
    printf("╚════════╩══════════════════╝\n");
}

int savegame_menu_graph(User user)
{

    printf("\nSelect Savegame (0 to quit)\n");
    for (int i = 0; i < 3; i++)
    {
        if (i < user.saveslotsN)
            printf("\n%d) %s\n", i + 1, user.saveslots[i].slotName);
        else
            printf("\n%d) EMPTY\n", i + 1);
    }
}
int inventaryDisplay(SaveSlot s, World w)
{
    Item it;
    if (s.itemsL == 0)
    {
        printf("No items in inventary\n");
        return 0;
    }
    else
    {
        printf("Inventary (%d):\n", s.itemsL);
        for (int i = 0; i < s.itemsL; i++)
        {
            it = getItemById(w, s.items[i].ID);
            printf("* %d) %s (x %d) \n> %s\n", i + 1, it.name, s.items[i].quantity, it.desc);
        }
        return 1;
    }
}
int inventarymanager(SaveSlot *s, World w)
{
    if (!inventaryDisplay(*s, w))
        return 0;
    char command[20];
    printf("What do you want to do?");
    printf("\nEMPTY - empty the whole inventary\nTHROW - throw away an item\nBACK - quit\n");
    do
    {
        fgets(command, 20, stdin);
        if (prefix("EMPTY", command) == 1)
        {
            (*s).itemsL = 0;
            printf("Threw all away");
            break;
        }
        else if (prefix("THROW", command) == 1)
        {
            printf("\nWhich? (0 for back)");
            int c = choicher(0, (*s).itemsL);
            if (c)
            {
                (*s).items[c - 1] = (*s).items[(*s).itemsL - 1];
                (*s).itemsL--;
                printf("\nThrew it away\n");
            }
            break;
        }
    } while (prefix("BACK", command) != 0);
}
int gameLoop(User u, GameFile gf, int selectedsss)
{

    SaveSlot s = u.saveslots[selectedsss];
    World w = getWorldById(gf, s.worldID);
    Room r = getRoom(w, s.roomID);
    musicTrack(r.musicFile);
    printf("<----------->\nWorld %d: %s - %s\n%s\n%s\n", w.ID, w.name, w.desc, r.name, r.desc);

    char command[20];
    do
    {
        fgets(command, 20, stdin);
        if (prefix("POCKET", command) == 1)
        {
            inventarymanager(&s, w);
        }
        else if (prefix("LOOK", command) == 1)
        {
            printf("You seee...");
            if (r.itemsN == 0)
                printf("\nNothing!");
            else
            {
                Item it;
                for (int i = 0; i < r.itemsN; i++)
                {
                    it = getItemById(w, r.items[i].ID);
                    printf("%d) %s\n>%s\n\n", i + 1, it.name, it.desc);
                }

                printf("Select the number of the item to pick (0 to quit)\n");
                int np = choicher(0, r.itemsN);
                if (!np)
                    continue;
                else if (s.itemsL == 10)
                {
                    printf("\nInventary is full!\n");
                }
                else
                {
                    ItemSave is;
                    Item ic;
                    ic = r.items[np - 1];
                    is.ID = ic.ID;
                    is.quantity = 1;
                    int alSet = 0;
                    for (int i = 0; i < s.itemsL; i++)
                    {
                        if (s.items[i].ID == ic.ID)
                        {
                            printf("\nYou already have this, incrementing\n");
                            s.items[i].quantity++;
                            alSet = 1;
                            break;
                        }
                    }
                    if (!alSet)
                    {
                        printf("\nAdded to inventary\n");
                        s.itemsL++;
                        s.items[s.itemsL - 1] = is;
                    }
                }
            }
        }
        else if (prefix("MOVE", command) == 1)
        {
            Room tr;
            if (r.pathsN == 0)
                printf("\nThere is nowhere to go\n");
            else
            {
                for (int i = 0; i < r.pathsN; i++)
                {
                    printf("%d) ", i + 1);
                    switch (r.paths[i].dir)
                    {
                    case N:
                        printf("\n North, ");
                        break;
                    case S:
                        printf("\n South, ");
                        break;
                    case E:
                        printf("\n East, ");
                        break;
                    case W:
                        printf("\n West, ");
                        break;
                    }
                    tr = getRoom(w, r.paths[i].toRoomId);
                    printf("to %s \n", tr.name);
                }
                printf("\n Which? (0 to quit)\n");
                int cc = choicher(0, r.pathsN);
                if (cc)
                {
                    r = getRoom(w, r.paths[cc - 1].toRoomId);
                    musicTrack(r.musicFile);
                    printf("<----------->\nWorld %d: %s - %s\n%s\n%s\n", w.ID, w.name, w.desc, r.name, r.desc);
                }
            }
        }
        s.roomID = r.ID;
        s.worldID = w.ID;
        u.saveslots[selectedsss] = s;
        saveUser(u);
    } while (prefix("QUIT", command) == 0);
}
int setSaveFile(GameFile gf, User *u, int i)
{
    if ((*u).saveslotsN < i + 1)
        (*u).saveslotsN++;
    printf("Save Slot %d", i + 1);
    printf("\nName: ");
    scanf("%s", (*u).saveslots[i].slotName);
    printf("\nWorld: ");
    printf("0) Back\n");
    for (int i = 0; i < gf.worldsN; i++)
    {
        printf("\n%d) %s\n>%s", i + 1, gf.worlds[i].name, gf.worlds[i].desc);
    }
    int c;
    c = choicher(0, gf.worldsN);
    (*u).saveslots[i].worldID = gf.worlds[c - 1].ID;
    (*u).saveslots[i].roomID = 1;
    saveUser(*u);
}