#include <stdio.h>
#include "../../../src/util/unit_type_conversion.h"


int main(void){
    int counter = 0;

    if(str_to_unit_type("gram") == 0 && str_to_unit_type("g") == 0){
        printf("Expected %d got %d\n", 0, str_to_unit_type("gram"));
    } else {
        printf("Expected %d got %d\n", 0, str_to_unit_type("gram"));
        return 1;
    }

    if(str_to_unit_type("kg") == 1 && str_to_unit_type("kilogram") == 1){
        printf("Expected %d got %d\n", 1, str_to_unit_type("kg"));
    } else {
        printf("Expected %d got %d\n", 1, str_to_unit_type("kg"));
        return 1;
    }

    if(str_to_unit_type("l" ) == 2 && str_to_unit_type("liter") == 2 && str_to_unit_type("ltr") == 2){
        printf("Expected %d got %d\n", 2, str_to_unit_type("l"));
    } else {
        printf("Expected %d got %d\n", 2, str_to_unit_type("l"));
        return 1;
    }

    if(str_to_unit_type( "ml") == 3 && str_to_unit_type("milliliter") == 3){
        printf("Expected %d got %d\n", 3, str_to_unit_type("ml"));
    } else {
        printf("Expected %d got %d\n", 3, str_to_unit_type("ml"));
        return 1;
    }

    if(str_to_unit_type("cl") == 4){
        printf("Expected %d got %d\n", 4, str_to_unit_type("cl"));
    } else {
        printf("Expected %d got %d\n", 4, str_to_unit_type("cl"));
        return 1;
    }

    if(str_to_unit_type( "each") == 5 && str_to_unit_type( "stk") == 5){
        printf("Expected %d got %d\n", 5, str_to_unit_type("each"));
    } else {
        printf("Expected %d got %d\n", 5, str_to_unit_type("each"));
        return 1;
    }

    if(str_to_unit_type( "mtr") == 6){
        printf("Expected %d got %d\n", 6, str_to_unit_type("each"));
    } else {
        printf("Expected %d got %d\n", 6, str_to_unit_type("each"));
        return 1;
    }

    if(str_to_unit_type( "saet") == 7){
        printf("Expected %d got %d\n", 7, str_to_unit_type("saet"));
    } else {
        printf("Expected %d got %d\n", 7, str_to_unit_type("saet"));
        return 1;
    }

    return 0;


}