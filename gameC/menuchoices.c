typedef enum MainMenuAction
{
    PLAY,
    CREDITS,
    NEWS,
    LOGOUT,
    DELETE
} MainMenuAction;

int choicher(int min, int max)
{
    int ch = min-1;
    while (ch < min || ch > max)
    {
        while (scanf("%d", &ch) != 1)
        {
            // Tell the user that the entry was invalid
            printf("??");
            // Asterisk * tells scanf to read and ignore the value
            scanf("%*s");
        }
        if (ch < min || ch > max)
            printf("??");
    }
    return ch;
}