#include <stdio.h>
#include <string.h>
#include "../../../src/util/string_utility.h"

int main(void){
    char *test_case = "This IS gRoup Six";
    str_to_lower(&test_case);
    puts("str_to_lower()");

    if(strcmp(test_case,"this is group six") == 0){
        printf("Expected this is group six got %s",test_case);
        return 0;
    } else {
        printf("Expected this is group six got %s",test_case);
        return 1;
    }

}