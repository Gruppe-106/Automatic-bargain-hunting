#include "user_io.h"
#include "../data_manager/data_manager.h"

typedef struct Input_Item {
    char* input;
    struct Input_Item *next_input;
} Input_Item;

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
Input_Item* user_input();

/**
 * @brief List stores in order of cheapest to most expensive
 * @param all_stores Store_Type prt, ptr to the list of all stores
 */
void user_output(Store_Type* all_stores);