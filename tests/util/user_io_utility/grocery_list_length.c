#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../../src/io/user_io.h"
#include "../../../src/util/user_io_utility.h"

int main(void){

    Input_Item
    *test_case_one = create_new_input_item("kød",1),
    *test_case_two = create_new_input_item("fisk",1),
    *test_case_three = create_new_input_item("ost",1);

    test_case_one->next_input = test_case_two;
    test_case_two->next_input = test_case_three;

    _Bool flag = true;
    /* Head of the list is given */
    int length = grocery_list_length(test_case_one);
    if( length == 3){
        printf("Expected 3 got %d",length);

    } else {
        printf("Expected 3 got %d",length);
        flag = false;
    }

    free(test_case_one->input);
    free(test_case_one);
    free(test_case_two->input);
    free(test_case_two);
    free(test_case_three->input);
    free(test_case_three);



    if(flag){
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }

}