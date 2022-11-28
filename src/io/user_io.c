/* Standard libraries */
#include <stdlib.h>
#include <string.h>

/* Custom libraries */
#include "user_io.h"
#include "../data_manager/data_manager.h"

/* Prototype */

/**
 * @brief Append an Input_Item to list
 * @param list Input_Item ptr, ptr to list to append too
 * @param input char*, the given input from user
 */
void append_input_item_node(Input_Item* list, char* input);

/**
 * @brief Gets user input using format\n
 * User input format: "something" enter "something" enter .... done enter
 * @return Input_Item ptr, linked list of all inputs
 */
Input_Item* user_input(Input_Item* item_list, char* item_input)
{
    /* we start by allocating space for a new item. The item already contains enough space for the item. */
    Input_Item* new_item = (Input_Item*) malloc(sizeof(Input_Item));

    /* If not allocated space exit */
    if(new_item == NULL)
        exit(EXIT_FAILURE);

    /* we use strcpy here because C does not support direct assignment. */
    strcpy(new_item->input, item_input);
}

/**
 * @brief deallocate, allocated memory from list
 * @param list Input_Item ptr, ptr to list to free
 */
void deallocate_user_input(Input_Item* list);

/**
 * @brief List stores in order of cheapest to most expensive
 * @param all_stores Store_Type prt, ptr to the list of all stores
 */
void user_output(Store_Type* all_stores);