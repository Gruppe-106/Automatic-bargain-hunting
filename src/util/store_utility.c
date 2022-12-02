

/* Standard libraires */
#include <stdio.h>
#include <stdlib.h>

/* Custom libraires */
#include "./store_utility.h"



int amount_of_stores(Store_Type *store){
    int length = 0;

    while (store)
    {
        store = store->next_node;
        length++;
    }
    return length;
}


/**
 * @brief Prints a stores items
 * @param store Store_Type*, store to print
 */
void print_store(Store_Type* store) {
    Item_Type **items = store->items;
    for (int i = 0; i < store->item_amount; ++i) {
        Item_Type *item = items[i];
        printf("======= %s - %d =======\n", store->name, i + 1);
        printf("Item: %s\n", item->name);
        printf("Price: %.2lf kr.\n", item->price);
        printf("Organic: %s\n", item->organic == 1 ? "yes" : "no");
        printf("Amount %.2lf %s\n\n", item->unit_size, item->unit != -1 ? unit_type_to_str(item->unit) : "NAN");
    }
}