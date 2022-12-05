#ifndef AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#define AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#include "../data_manager/data_manager.h"
#include "../util/user_io_utility.h"

typedef struct {
    char* query;
    Item_Type** items_result;
    size_t items_len;
} Query_Result_Type;

typedef struct {
    char* store;
    Query_Result_Type** results;
    int results_len;
} Store_Result_Type;

Store_Result_Type *search_store(Input_Item *query_items, Store_Type* store);
void free_query(Item_Type** query_result);
Item_Type** find_items(const char* query, Item_Type** items, size_t size, size_t* size_output);
void print_results(Store_Result_Type** store_res, size_t store_size);
Store_Result_Type **search_stores(Input_Item *query_items, Store_Type* all_stores, size_t *results_len);
void sort_stores_items(Store_Type **all_stores);
void free_results(Store_Result_Type** store_res, size_t store_size);
#endif //AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
