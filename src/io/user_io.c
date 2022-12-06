/* Standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

/* Custom libraries */
#include "user_io.h"
#include "../util/string_utility.h"
#include "../util/user_io_utility.h"
#include "../util/node_handler.h"

/**
 * @brief Create a new input item struct
 *
 * @param name name of item
 * @return Input_Item struct
 */
Input_Item *create_new_input_item(char *name, int quantity)
{

    Input_Item *new_item = (Input_Item *)malloc(sizeof(Input_Item));
    new_item->next_input = NULL;
    new_item->input = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    new_item->quantity = quantity;

    str_to_lower(&name);
    memcpy(new_item->input, name, strlen(name) + 1);

    return new_item;
}

/**
 * @brief Append an Input_Item to list
 * @param list Input_Item ptr, ptr to list to append too
 * @param input char*, the given input from user
 */
void append_input_item_node(Input_Item *input_list, char *input, int quantity)
{
    int length = grocery_list_length(input_list);
    Input_Item *new_item = create_new_input_item(input, quantity);

    for (int i = 0; i < length; i++)
    {
        input_list = input_list->next_input;
    }

    input_list->next_input = new_item;
};

/**
 * @brief Gets user input using format\n
 * User input format: "something" enter "something" enter .... done enter
 * @return Input_Item ptr, linked list of all inputs
 */
Input_Item *input_grocery_list()
{
    _Bool flag = false;
    _Bool quit = false;
    char *name = (char*)malloc(sizeof(char)*100);
    Input_Item *grocery_list = NULL;

    puts("Enter grocery list");
    while (!flag)
    {
        printf("Enter item > ");
        fgets(name, 100,stdin);
        str_to_lower(&name);

        /* Removes leading newlines*/
        if ((strlen(name) > 0) && (name[strlen (name) - 1] == '\n'))
            name[strlen (name) - 1] = '\0';


        if (strcmp(name, "find") == 0)
        {
            if(grocery_list_length(grocery_list) == 0){
                puts("No items has been entered");
                continue;
            }
            print_grocery_list(grocery_list);
            flag = true;
        }
        else if (strcmp(name, "quit") == 0)
        {
            flag = true;
            quit = true;
        }
        else
        {
            read_item_string(name, &grocery_list); /* Reads the input and creates a new item */
        }
    }

    if(quit){
        free(name);
        free_grocery_list(grocery_list);
        exit(EXIT_SUCCESS);
    } else {
        return grocery_list;
    }

}


/**
 * @brief Reads a given item_string
 * 
 * @param string The itemstring to read
 * @param grocery_list The grocerylist
 */
void read_item_string(char *string, Input_Item **grocery_list)
{
    if (str_contains_str(string, ":", false) != -1)
    {
        char delimiter[1] = ":";
        char *name   = strtok(string,delimiter);
        int quantity = atoi(strtok(NULL,delimiter)); /* TODO: use strtol */

        if (*grocery_list == NULL)
        {
            *grocery_list = create_new_input_item(name,quantity);
        }
        else
        {
            append_input_item_node(*grocery_list, name, quantity);
        }
    }
    else
    {
        if (*grocery_list == NULL)
        {
            *grocery_list = create_new_input_item(string,1);
        }
        else
        {
            append_input_item_node(*grocery_list, string,1);
        }
    }
}