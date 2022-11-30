/* Standard libraries */
#include <stdlib.h>


/* Custom libraries */
#include "node_handler.h"

/* ================================================== *
 *      De-allocation of store and members within     *
 * ================================================== */

/**
 * @brief Frees the item along with the name
 * @param item Item_Type, item to be freed.
 */
void free_item(Item_Type* item) {
    //First free the name & then the item itself
    free(item->name);
    free(item);
}

/**
 * @brief Frees an array of items, with length item_count
 * @param items ptr, pointer to the first index value
 * @param item_count int, amount of items in the array
 */
void free_items(Item_Type** items, size_t item_amount) {
    //Go through all items in the list & free the items
    for (int i = 0; i < item_amount; ++i) {
        free_item(items[i]);
    }
}

/**
 * Frees a store and all it's members
 * @param store Store_Type ptr, ptr to store to free from heap
 */
void free_store(Store_Type* store) {
    //Free the item list
    free_items(store->items, store->item_amount);
    //Free the name
    free(store->name);
    //Free the store itself
    free(store);
}

/**
 * @brief Free a node-based Store_Type list and everything within it
 * @param all_stores Store_Type ptr, for all stores to free
 */
void free_stores(Store_Type* all_stores) {
    //Check if any amount of stores exists or return, to avoid freeing memory of range
    if (all_stores == NULL) return;
    //Get the first store node
    Store_Type* next = all_stores;
    //Go through all the stores until a null pointer is found
    while (next->next_node != NULL) {
        Store_Type *to_free = next;
        next = next->next_node;
        free_store(to_free);
    }
}
