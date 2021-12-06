#include "gamedata.c"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void sanitizeJsonStringField(char *jsf)
{
    for (int i = 0; i < strlen(jsf); i++)
    {
        if (jsf[i] == '"')
            jsf[i] = '\'';
        else if (jsf[i] == '\\')
            jsf[i] = ' ';
        else if (jsf[i] == '\n')
            jsf[i] = '-';
    }
}
int main()
{

    FILE *fp;
    GameFile gf;
    if ((fp = fopen("./gameC/gamefile.obj", "rb")) == NULL)
    {
        printf("Could not open file");
        exit(1);
    }

    fread(&gf, sizeof(gf), 1, fp);
    fclose(fp);
    char c;
    printf("{\n");
    printf("    \"uid\": %d,\n", gf.uid);
    printf("    \"worlds\": [\n");
    for (int i = 0; i < gf.worldsN; i++)
    {
        printf("        {\n");
        printf("            \"ID\": %d,\n", gf.worlds[i].ID);
        sanitizeJsonStringField(gf.worlds[i].name);
        printf("            \"name\": \"%s\",\n", gf.worlds[i].name);
        sanitizeJsonStringField(gf.worlds[i].desc);
        printf("            \"desc\": \"%s\",\n", gf.worlds[i].desc);
        printf("            \"rooms\": [\n");
        for (int j = 0; j < gf.worlds[i].roomsN; j++)
        {
            printf("                {\n");
            printf("                    \"ID\": %d,\n", gf.worlds[i].rooms[j].ID);
            sanitizeJsonStringField(gf.worlds[i].rooms[j].name);
            printf("                    \"name\": \"%s\",\n", gf.worlds[i].rooms[j].name);
            sanitizeJsonStringField(gf.worlds[i].rooms[j].desc);
            printf("                    \"desc\": \"%s\",\n", gf.worlds[i].rooms[j].desc);
            sanitizeJsonStringField(gf.worlds[i].rooms[j].musicFile);
            printf("                    \"musicFile\": \"%s\",\n", gf.worlds[i].rooms[j].musicFile);
            printf("                    \"paths\": [\n");
            for (int k = 0; k < gf.worlds[i].rooms[j].pathsN; k++)
            {
                printf("                        {\n");
                if (gf.worlds[i].rooms[j].paths[k].dir == 0)
                    c = 'N';
                else if (gf.worlds[i].rooms[j].paths[k].dir == 1)
                    c = 'S';
                else if (gf.worlds[i].rooms[j].paths[k].dir == 2)
                    c = 'E';
                else if (gf.worlds[i].rooms[j].paths[k].dir == 3)
                    c = 'W';
                printf("                            \"dir\": \"%c\",\n", c);
                printf("                            \"toRoomId\": %d\n", gf.worlds[i].rooms[j].paths[k].toRoomId);
                printf("                        }");
                if (k != gf.worlds[i].rooms[j].pathsN - 1)
                    printf(",");
                printf("\n");
            }
            printf("                    ],\n");
            printf("                    \"items\": [\n");
            for (int k = 0; k < gf.worlds[i].rooms[j].itemsN; k++)
            {
                printf("                        {\n");
                printf("                            \"ID\": %d,\n", gf.worlds[i].rooms[j].items[k].ID);
                sanitizeJsonStringField(gf.worlds[i].rooms[j].items[k].name);
                printf("                            \"name\": \"%s\",\n", gf.worlds[i].rooms[j].items[k].name);
                sanitizeJsonStringField(gf.worlds[i].rooms[j].items[k].desc);
                printf("                            \"desc\": \"%s\",\n", gf.worlds[i].rooms[j].items[k].desc);
                printf("                            \"healtheffect\": %d\n", gf.worlds[i].rooms[j].items[k].healtheffect);
                printf("                        }");
                if (k != gf.worlds[i].rooms[j].itemsN - 1)
                    printf(",");
                printf("\n");
            }
            printf("                    ]\n");
            printf("                }");
            if (j != gf.worlds[i].roomsN - 1)
                printf(",");
            printf("\n");
        }
        printf("            ]\n");
        printf("        }\n");
    }
    printf("    ]\n");
    printf("}\n");
}