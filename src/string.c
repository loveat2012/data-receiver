#include <ctype.h>
#include <string.h>
#include "string.h"


char *ltrim(char *string)
{
    while (isspace(*string))
        string++;
    return string;
}

char *rtrim(char *string)
{
    char *end = string + strlen(string) - 1;
    while (end > string && isspace(*end)) {
        end--;
    }
    *(++end) = '\0';
    return string;
}

char *trim(char *string)
{
    if (strlen(string) > 0) {
        while (isspace(*string)) {
            string++;
        }
        char *end = string + strlen(string) - 1;
        while (end > string && isspace(*end)) {
            end--;
        }
        *(++end) = '\0';
    }
    return string;
}
