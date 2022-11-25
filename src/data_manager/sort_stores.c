#include "sort_stores.h"
#include <stdlib.h>

int compare_price_of_items(const void *p, const void *q);

/**
 * Sorts the list of items for one store using qsort()
 * @param store Store_Type ptr, ptr to store node needing to be sorted
 */
Store_Type *sort_store_items(Store_Type *store)
{
    Item_Type** itemsSorted = store->items;
    qsort(store->items, store->item_amount, sizeof(Item_Type*), compare_price_of_items);
    store->items = itemsSorted;

    return store;
}

int compare_price_of_items(const void *p, const void *q)
{
    Item_Type* item1 = *(Item_Type**)p;
    Item_Type* item2 = *(Item_Type**)q;
    if (item1->price < item2->price)
        return -1;
    else if (item1->price > item2->price)
        return 1;
    else
        return 0;
}