#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../../src/util/unit_type_conversion.h"

/* TODO: MAKE MORE EFFICIENT */
int main(void){

    puts("unit_type_to_str()");

    if(strcmp("g", unit_type_to_str(GRAM)) == 0){
        printf("Expected g got g\n");
    } else {
        printf("Expected g got %s",unit_type_to_str(GRAM));
        return EXIT_FAILURE;
    }

    if(strcmp("kg", unit_type_to_str(KILOGRAM)) == 0){
        printf("Expected kg got kg\n");
    } else {
        printf("Expected kg got %s",unit_type_to_str(KILOGRAM));
        return EXIT_FAILURE;
    }

    if(strcmp("l", unit_type_to_str(LITER)) == 0){
        printf("Expected l got l\n");
    } else {
        printf("Expected l got %s",unit_type_to_str(LITER));
        return EXIT_FAILURE;
    }

    if(strcmp("ml", unit_type_to_str(MILLILITER)) == 0){
        printf("Expected ml got ml\n");
    } else {
        printf("Expected ml got %s",unit_type_to_str(MILLILITER));
        return EXIT_FAILURE;
    }

    if(strcmp("each", unit_type_to_str(EACH)) == 0){
        printf("Expected each got each\n");
    } else {
        printf("Expected each got %s",unit_type_to_str(EACH));
        return EXIT_FAILURE;
    }

    if(strcmp("cl", unit_type_to_str(CENTILITER)) == 0){
        printf("Expected cl got cl\n");
    } else {
        printf("Expected cl got %s",unit_type_to_str(CENTILITER));
        return EXIT_FAILURE;
    }

    if(strcmp("m", unit_type_to_str(METER)) == 0){
        printf("Expected m got m\n");
    } else {
        printf("Expected m got %s",unit_type_to_str(METER));
        return EXIT_FAILURE;
    }

    if(strcmp("set", unit_type_to_str(SET)) == 0){
        printf("Expected set got set\n");
    } else {
        printf("Expected set got %s",unit_type_to_str(SET));
        return EXIT_FAILURE;
    }

    if(strcmp("", unit_type_to_str(9)) == 0){
        printf("Expected "" got "" \n");
    } else {
        printf("Expected "" got %s",unit_type_to_str(SET));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}