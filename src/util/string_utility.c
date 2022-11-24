#include "string_utility.h"
#include <ctype.h>
#include <string.h>
#define NOTFOUND -1

/**
 * @brief Converts char* pointer to lowercase
 * @param string char* ptr, string to convert
 */
void str_to_lower(char **string) {
    //Duplicate string to avoid memory errors
    char* str_dup = strdup(*string);
    //Run through string until end character is found
    for (size_t i = 0; str_dup[i] != '\0'; ++i)
        str_dup[i] = (char) tolower(str_dup[i]);
    //Set inputted string to lowercase version
    *string = str_dup;
}

/**
 * Looks for a string in a string
 * @param string char*, string to search
 * @param to_find char*, string to find
 * @param case_sensitive _Bool, whether to ignore case
 * @return index of first letter if found, otherwise -1
 */
int str_contains_str(char* string, char* to_find, _Bool case_sensitive) {
    if (!case_sensitive) {
        str_to_lower(&string);
        str_to_lower(&to_find);
    }
    //Loop through string by each char
    for (int i = 0; string[i] != '\0'; ++i) {
        //Find the first char in string
        if (string[i] == to_find[0]) {
            int count = 1;
            //Keep checking until either full string found, out of bounds on either strings or character didn't match
            for (int j = 1; to_find[j] != '\0' && string[i + j] != '\0' && to_find[j] == string[i + j]; ++j)
                ++count;
            //Check if a string match was found, if so return index of first char
            if (count == strlen(to_find)) return i;
        }
    }
    return NOTFOUND;
}
