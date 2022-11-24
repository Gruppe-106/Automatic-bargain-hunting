#include "rank_stores.h"
#include "stdio.h"
#include "stdlib.h"



// typedef struct item {
//     char* name;
//     double price;
//     int unit_size;
//     Unit_Type unit;
//     _Bool organic;
// } Item_Type;

// typedef struct store {
//     char* name;
//     Item_Type** items;
//     size_t item_amount;
//     double total_price;
//     struct store* next_node;
// } Store_Type;

/**
 * Get total price for one store and update the ptr total_price
 * @param store Store_Type ptr, store to search for all items and get total price from
 */
void get_total_for_store(Store_Type* store){
    double current_total = 0;

    if(!store){
        return;
    } else {
        for (int i = 0; i < store->item_amount; i++)
        {
            current_total += store->items[i]->price;
        }
        store->total_price = current_total;
    }

}

/**
 * Uses get_total_for_store to get total for all stores in all stores linked list
 * @param all_stores Store_Type ptr, ptr to all store linked list
 */
void rank_all_stores(Store_Type* all_stores){
    double current_total = 0;

    if(!all_stores){
        return;
    } else {
        for (int i = 0; i < all_stores->item_amount; i++)
        {
            current_total += all_stores->items[i]->price;
        }

        all_stores->total_price = current_total;
        rank_all_stores(all_stores->next_node);
    }

}


// ved ikke hvorfor jeg lavede det her XD
//int sort_total_price (const void * a, const void * b);

// int sort_total_price (const void * a, const void * b) {
//     Store_Type *store_one = (Store_Type*)a;
//     Store_Type *store_two = (Store_Type*)b;

//     if(store_one->total_price > store_two->total_price){
//         return 1;
//     } else if(store_one->total_price < store_two->total_price){
//         return -1;
//     } else {
//         return 0;
//     }

// }
