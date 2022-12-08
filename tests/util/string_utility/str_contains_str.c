

#include <stdbool.h>
#include <stdio.h>
#include "../../../src/util/string_utility.h"

int main(void){
    puts("str_contains_str()");
    int test_location = str_contains_str("hello my name is Frank","name",false);

    if(test_location >= 0){
        printf("Expected 9 got %d ",test_location);
        return 0;
    } else {
        printf("Expected 9 got %d ",test_location);
        return 1;
    }
}