#include "search.h"
#include <stdlib.h>

/* Prototypes */
/**
 * Find the cheapest item in a sorted list of Item_Type in a store node
 * @param store Store_Type ptr, a single store as a ptr
 * @param item char*, a string query for what to find in the item list
 * @return Item_Type ptr, ptr to the cheapest item found matching query or NullPointerReference
 */
Item_Type* find_cheapest_item_in_store(Store_Type *store, char* query);
int get_length_of_items(Item_Type** items);
int str_contains_str_test(const char* original, const char* str_to_find);

/* Definitions */
/**
 * @brief Gets the length of items under the assumption that items ends in a NULL pointer
 * @param items array of item pointers, ending in NULL
 * @return the length of the array of item pointers, not including NULL pointer. An array of one valid pointer returns len = 1.
 */
int get_length_of_items(Item_Type** items)
{
    int i = 0;
    while (items[i] != NULL) ++i;
    return i;
} /* TODO: Not walked through. Not tested. Edge cases? */

/**
 * @brief Dynamically allocates a return type of Item_Type** to be freed.\n
 * Finds items that contain the query query, in a list of items.
 * @param query char*, the query.
 * @param items Item_Type**, the items that we will be going through.
 * @return Returns an array of item pointers, Item_Type**, that match the query.
 */
Item_Type** find_items_in_items_by_str(char* query, Item_Type** items)
{
    /*
     * Creates a temporary array (items_match) which will be freed when function is done automatically.
     * It has the length of len because matching items count can impossibly exceed the length of the array 'items'.
     */
    int len = get_length_of_items(items);
    Item_Type* items_match[len];
    int valid_items_len = 0;

    /* Proceeds to find all names matching the query, appends them to the temporary array 'items_match'. */
    for (int i = 0; i < len; ++i) {
        Item_Type* item_ptr = items[i];
        if (str_contains_str_test(item_ptr->name, query))
        {
            items_match[valid_items_len] = items[i];
            ++valid_items_len;
        }
    }

    /*
     * Now that we know how many matching cases there is, we dynamically allocate an array of item pointers to return.
     * This array of item pointers will be ending in a NULL pointer. We then copy the values of the temporary array
     * to the new array that we will return.
     */
    Item_Type** lst_to_return = (Item_Type**) malloc(sizeof(Item_Type*) * (valid_items_len + 1));

    for (int i = 0; i < valid_items_len; ++i)
    {
        lst_to_return[i] = items_match[i];
    }
    lst_to_return[valid_items_len] = NULL;

    return lst_to_return;
} /* TODO: Not walked through. Not tested. Do I allocate memory for an entire list of items or just item pointers? */

/**
 * @brief Checks if str_to_find is contained in original
 * @param original str, checks if it contains str_to_find
 * @param str_to_find str, checks if it is contained in original
 * @return Returns 1 if str_to_find is contained in original. Otherwise returns 0
 */
int str_contains_str_test(const char* original, const char* str_to_find)
{
    int
        i = 0,
        i_query = 0;

    char
        c = original[i],
        c_query = str_to_find[i_query];

    while (c != '\0')
    {
        if (c == c_query) i_query++;
        else if (c_query == '\0') return 1;
        else i_query = 0;

        i++;
        c_query = str_to_find[i_query];
        c = original[i];
    }
    if (c_query == '\0') return 1;
    else return 0;
} /* TODO: Not walked through. Limited testing. */

/*
 * I do not understand this function from the name of it. If my goal is to find the cheapest item, then why do I have an item parameter?
 * If the goal is to find an item, like this item parameter, then it would be highly unlikely for  it to be there.
 * If it is meant to search for the item name, and then find the item, it's doable, but item parameter is overkill opposed to str parameter.
 */ /* TODO: Find the true meaning of 'find_cheapest_item_in_store' */
Item_Type* find_cheapest_item_in_store(Store_Type *store, char* query)
{
    return NULL;
}