#include <string.h>
#include <stdio.h>
void logo()
{
    printf("  █████▒▒█████   ▒█████   ██▓    \n");
    printf("▓██   ▒▒██▒  ██▒▒██▒  ██▒▓██▒    \n");
    printf("▒████ ░▒██░  ██▒▒██░  ██▒▒██░    \n");
    printf("░▓█▒  ░▒██   ██░▒██   ██░▒██░    \n");
    printf("░▒█░   ░ ████▓▒░░ ████▓▒░░██████▒\n");
    printf("Mattia Mascarello, Giacomo Roggero \n             v. 1.0 \n 2021   \n");
}
int main_menu(){
    printf("╔═══════════════════════════╗\n");
    printf("║        Main Menu             ║\n");
    printf("╠════════╦══════════════════╣\n");
    printf("║ Option  ║      Action        ║\n");
    printf("╠════════╬══════════════════╣\n");
    printf("║      1  ║ Play Locally       ║\n");
    printf("║      2  ║ Play online        ║\n");
    printf("║      3  ║ Read recent news   ║\n");
    printf("║      4  ║ Settings           ║\n");
    printf("╚════════╩══════════════════╝\n");
}
int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    logo();
    main_menu();
    scanf("%s");
}