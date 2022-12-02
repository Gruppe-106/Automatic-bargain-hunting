/* Standard libraries */
#include <stdio.h>

/* Custom libraries */
#include "user_io_utility.h"


int grocery_list_length(Input_Item* grocery_list){

    int length = 0;

    Input_Item* current = grocery_list;

    if(grocery_list != NULL){
        while(grocery_list->next_input){
            length++;
            current = current->next_input;
        }
    }
    return length;
}



void print_grocery_list(Input_Item* grocery_list){
    int length = grocery_list_length(grocery_list);
    puts("Grocery list");
    if(length == 0){
        puts("Grocery list is empty");
    } else {
        for (int i = 0; i < length; i++)
        {
            printf("%d:  %s", i+1, grocery_list->input);
            grocery_list = grocery_list->next_input;
        }
    }

}
