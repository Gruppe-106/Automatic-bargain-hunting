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
    int missing_items;
    double price_of_groceries;
} Store_Result_Type;
void print_results(size_t length, Store_Result_Type *const *results);
void sort_results(Store_Result_Type ***stores, size_t length);
void print_search_data(Store_Result_Type** store_res, size_t store_size);
Store_Result_Type **search_stores(Input_Item *query_items, Store_Type* all_stores, size_t *results_len_output);
void free_results(Store_Result_Type** store_res, size_t store_size);
#endif //AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
