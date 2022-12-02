/* Standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

/* Custom libraries */
#include "user_io.h"
#include "../util/string_utility.h"
#include "../data_manager/data_manager.h"
#include "../util/user_io_utility.h"


/**
 * @brief Create a new input item struct
 * 
 * @param name name of item
 * @return Input_Item struct
 */
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
void append_input_item_node(Input_Item* input_item, char* input){
    int length           = grocery_list_length(input_item);
    Input_Item* new_item = create_new_input_item(input);

    for (int  i = 0; i < length; i++)
    {
        input_item = input_item->next_input;
    }

    input_item->next_input = new_item;

   
};

/**
 * @brief Gets user input using format\n
 * User input format: "something" enter "something" enter .... done enter
 * @return Input_Item ptr, linked list of all inputs
 */
Input_Item* user_driver()
{
    _Bool flag = false;
    char* name;
    Input_Item *grocery_list;
    puts("Enter grocery list");
    while(!flag){
        printf ("Enter item > ");
        scanf  ("%s", &name);
        str_to_lower(&name);

        if( strcmp(name, "find") == 0 ){
            /* RETURN MAIN FUNCTION HERE */
            print_grocery_list(grocery_list);
            return grocery_list;
            flag = true;
        }else
        if( strcmp(name, "quit") == 0 ) {
            flag = true;
            break;
        } else {

            if(grocery_list == NULL){
                grocery_list = create_new_input_item(name);
            } else {
                append_input_item_node(grocery_list, name);
            }

        }
    }

    free_grocery_list(grocery_list);
}


/**
 * @brief Frees the grocery list
 * 
 * @param grocery_list the grocery list
 */
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


