/* Standard libraries */
#include <stdlib.h>

/* Custom libraries */
#include "sort_stores.h"

int compare_price_of_items(const void *p, const void *q);

/**
 * Sorts the list of items for one store using qsort()
 * @param store Store_Type ptr, ptr to store node needing to be sorted
 * @return returns a store with a sorted list of items
 */
Store_Type *sort_store_items(Store_Type *store)
{
    /* Quick sort */
    qsort(store->items, store->item_amount, sizeof(Item_Type*), compare_price_of_items);

    return store;
}

/**
 * Comparator function for qsort()
 * @param p &
 * @param q A const void pointer that can hold address of any const type and can be type-casted to any const type
 * @return returns either -1, 0, or 1 to show which price is less/cheaper than the other, used in qsort to sort after det cheapest item first
 */
int compare_price_of_items(const void *p, const void *q)
{
    Item_Type* item1 = *(Item_Type**)p;
    Item_Type* item2 = *(Item_Type**)q;

    if (item1->price < item2->price) return -1;
    else if (item1->price > item2->price) return 1;
    else return 0;
}