#include "search.h"

/**
 * Find the cheapest item in a sorted list of Item_Type in a store node
 * @param store Store_Type ptr, a single store as a ptr
 * @param item char*, a string query for what to find in the item list
 * @return Item_Type ptr, ptr to the cheapest item found matching query or NullPointerReference
 */
Item_Type* find_cheapest_item_in_store(Store_Type *store, char* item);