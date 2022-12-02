/* Standard libraries */
#include <string.h>

/* Custom libraires */
#include "unit_type_conversion.h"
#include "string_utility.h"


/**
 * Converts a string to a Unit_Type if exist
 * @param str char*, string to check
 * @return Unit_Type, if applicable otherwise -1
 */
Unit_Type str_to_unit_type(char* str) {
    str_to_lower(&str);
    if (strcmp(str, "g") == 0 || strcmp(str, "gram") == 0 || strcmp(str, "gr") == 0)
        return GRAM;
    else if (strcmp(str, "kg") == 0 || strcmp(str, "kilogram") == 0)
        return KILOGRAM;
    else if (strcmp(str, "l" ) == 0 || strcmp(str, "liter") == 0 || strcmp(str, "ltr") == 0)
        return LITER;
    else if (strcmp(str, "ml") == 0 || strcmp(str, "milliliter") == 0)
        return MILLILITER;
    else if (strcmp(str, "each") == 0 || strcmp(str, "stk") == 0)
        return EACH;
    else if (strcmp(str, "cl") == 0)
        return CENTILITER;
    else if (strcmp(str, "mtr") == 0)
        return METER;
    else if (strcmp(str, "saet") == 0)
        return SET;
    return -1;
}

/**
 * Converts a Unit_Type to a string if exist
 * @param unit_type Unit_Type, Unit_type to convert
 * @return char*, name of Unit_Type or ""
 */
char* unit_type_to_str(Unit_Type unit_type) {
    switch (unit_type) {
        case GRAM:
            return "g";
        case KILOGRAM:
            return "kg";
        case LITER:
            return "l";
        case MILLILITER:
            return "ml";
        case EACH:
            return "each";
        case CENTILITER:
            return "cl";
        case METER:
            return "m";
        case SET:
            return "set";
        default:
            return "";
    }
}