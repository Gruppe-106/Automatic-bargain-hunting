#include "utility.h"


/**
 * @brief creates a lowercase string
 *
 * @param s string to make lowercase
 * @return  lowercase string
 */
char *toLower(char *s)
{
	for (char *p = s; *p; p++)
		*p = tolower(*p);
	return s;
}

