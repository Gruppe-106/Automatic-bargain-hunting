#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../src/io/user_io.h"
#include "../../src/util/user_io_utility.h"
#include "../../src/util/node_handler.h"

int main(void){
    Input_Item *test_case = input_grocery_list(true);
    Input_Item *current = test_case;
    int length = grocery_list_length(test_case);

    puts("User_io test");


    if(length != 10){
        free_grocery_list(test_case);
        printf("Expected a length of 10 got %d",length);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 10; ++i) {
        if(strcmp(current->input,"test") != 0){
            printf("Expected input to be test got %s",current->input);
            free_grocery_list(test_case);
            return EXIT_FAILURE;
        } else if(current->quantity != 1){
            printf("Expected a quantity of 1 got %d",current->quantity);
            free_grocery_list(test_case);
            return EXIT_FAILURE;
        } else {
            printf("test case %d: Expected input to be test got %s\n",i+1,current->input);
            printf("test case %d: Expected a quantity of 1 got %d\n", i+1, current->quantity);
            current = current->next_input;
        }
    }

    free_grocery_list(test_case);
    return EXIT_SUCCESS;



}