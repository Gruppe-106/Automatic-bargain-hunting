/* Standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/* Custom libraries */
#include "user_io.h"
#include "../data_manager/data_manager.h"
#include "../util/user_io_utility.h"
#include "../util/user_io_utility.c"

/* Prototype */


Input_Item* create_new_input_item(char* name){

    Input_Item* new_item = (Input_Item*) malloc(sizeof(Input_Item));
    new_item->next_input = NULL;
    char *item_name      = (char*) malloc(sizeof(char)*(strlen(name)+1));

    str_to_lower(&name);
    memcpy(new_item->input, name, strlen(name) + 1);

    return new_item;
}

/**
 * @brief Append an Input_Item to list
 * @param list Input_Item ptr, ptr to list to append too
 * @param input char*, the given input from user
 */
void append_input_item_node(Input_Item** input_item, char* input){
    if((*input_item)->next_input == NULL){
        (*input_item)->next_input = create_new_input_item(input);
        return;
    } else {
        append_input_item_node((*input_item)->next_input, input);
    }
};

/**
 * @brief Gets user input using format\n
 * User input format: "something" enter "something" enter .... done enter
 * @return Input_Item ptr, linked list of all inputs
 */
void user_driver()
{
    _Bool flag = false;
    char* name;
    Item_Type *grocery_list;

    while(!flag){
        scanf  ("%s", &name);
        tolower(&name);

        if( strcmp(name, "find") == 0 ){
            /* CALL MAIN FUNCTION HERE */
            break;
        }else
        if( strcmp(name, "quit") == 0 ) {
            /* FREE THINGS */
            break;
        } else {

            if(grocery_list == NULL){
                grocery_list = create_new_input_item(name);
            } else {
                append_input_item_node(&grocery_list, name);
            }

        }
    }
}


void free_grocery_list(Input_Item* grocery_list){
    int length = grocery_list_length(grocery_list);

    Input_Item* next    = grocery_list->next_input;
    Input_Item* current = grocery_list;

    for (int i = 0; i < length; i++)
    {
        free(current->input);
        free(current);
        current = next;
        next = next->next_input;
    }

}


// /**
//  * @brief deallocate, allocated memory from list
//  * @param list Input_Item ptr, ptr to list to free
//  */
// void deallocate_user_input(Input_Item* list);

// /**
//  * @brief List stores in order of cheapest to most expensive
//  * @param all_stores Store_Type prt, ptr to the list of all stores
//  */
// void user_output(Store_Type* all_stores);