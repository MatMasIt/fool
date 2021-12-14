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
    printf("║      1  ║ Play Locally       ║\n");
    printf("║      2  ║ Play online        ║\n");
    printf("║      3  ║ Read recent news   ║\n");
    printf("║      4  ║ Settings           ║\n");
    printf("║      5  ║ Logout             ║\n");
    printf("║      6  ║ Delete             ║\n");
    printf("╚════════╩══════════════════╝\n");
}

int savegame_menu_graph(User user)
{

    printf("\nSelect Savegame\n");
    for (int i = 0; i < 3; i++)
    {
        if(i<user.saveslotsN-1) printf("\n%d) %s\n", i + 1, user.saveslots[i].slotName);
        else printf("\n%d) EMPTY\n", i + 1);
    }
}
void gameLoop(User u, GameFile gf, int selectedsss){
    u.saveslots[selectedsss].roomID;
}