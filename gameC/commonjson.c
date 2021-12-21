/** @file commonjson.c
 *  @brief Common Json functions
 *  This contains all functions pertaining
 *  to handling and producing json files
 *
 *  @author Mattia Mascarello (MatMasIt)
 *  @bug Newlines are replaced by a dash character.
 *  @version 1.0
 *  @date 2021-12-21
 *
 *  @copyright MIT LICENSE 2021
 */
#include <string.h>
/**
       * @brief  Sanitizes a string to be put in a json field
       * @param jsf string to sanitize
       * @return None
*/
void sanitizeJsonStringField(char *jsf)
{
    for (int i = 0; i < strlen(jsf); i++) // iterate over characters
    {
        if (jsf[i] == '"') // replace illegal double quote with single quote
            jsf[i] = '\'';
        else if (jsf[i] == '\\') // replace illegal backslash with space
            jsf[i] = ' ';
        else if (jsf[i] == '\n') // remove illegal \n with -
            jsf[i] = '-';
    }
}