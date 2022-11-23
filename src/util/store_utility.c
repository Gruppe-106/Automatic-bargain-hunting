#include "store_utility.h"
#include "stdio.h"
#include "stdlib.h"



int amount_of_stores(Store_Type *store){
    int length = 0;

    while (store)
    {
        store = store->next_node;
        length++;
    }
    return length;
}