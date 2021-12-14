#include "playerdata.c"
#include "commonjson.c"
int main()
{
    UserSave us = loadList();
    printf("{\n");
    printf("    \"users\": [\n");
    for (int i = 0; i < us.userN; i++)
    {
        printf("        {\n");
        sanitizeJsonStringField(us.userList[i].username);
        printf("            \"username\": \"%s\",\n", us.userList[i].username);
        sanitizeJsonStringField(us.userList[i].email);
        printf("            \"email\": \"%s\",\n", us.userList[i].email);
        printf("            \"initialized\": ");
        if (us.userList[i].initialized)
        {
            printf("true,\n");
        }
        else
        {

            printf("false,\n");
        }
        printf("            \"creationTime\": %d,\n", us.userList[i].creationTime);
        printf("            \"saveSlots\": [\n");

        for (int j = 0; j < us.userList[i].saveslotsN; j++)
        {
            printf("                {\n");
            printf("                    \"worldId\": %d,\n", us.userList[i].saveslots[j].worldID);
            printf("                    \"roomId\": %d,\n", us.userList[i].saveslots[j].roomID);
            sanitizeJsonStringField(us.userList[i].saveslots[j].slotName);
            printf("                    \"slotName\": \"%s\",\n", us.userList[i].saveslots[j].slotName);
            printf("                    \"items\": [\n");
            for (int k = 0; k < us.userList[i].saveslots[j].itemsL; k++)
            {
                printf("                        {\n");
                printf("                            \"id\": %d,\n", us.userList[i].saveslots[j].items[k].ID);
                printf("                            \"quantity\": %d\n", us.userList[i].saveslots[j].items[k].quantity);
                printf("                        }\n");
                if (k != us.userList[i].saveslots[j].itemsL - 1)
                    printf(",");
            }
            printf("                    ]\n");
            printf("                }\n");
            if (j != us.userList[i].saveslotsN - 1)
                printf(",");
        }
        printf("            ]\n");
        printf("        }\n");
        if (i != us.userN - 1)
            printf(",");
    }
    printf("    ]\n");
    printf("}\n");
}