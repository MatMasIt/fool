#include "string.h"
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