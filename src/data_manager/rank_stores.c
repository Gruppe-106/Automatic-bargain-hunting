#include "rank_stores.h"

/**
 * Get total price for one store and update the ptr total_price
 * @param store Store_Type ptr, store to search for all items and get total price from
 */
void get_total_for_store(Store_Type* store);

/**
 * Uses get_total_for_store to get total for all stores in all stores linked list
 * @param all_stores Store_Type ptr, ptr to all store linked list
 */
void rank_all_stores(Store_Type* all_stores);