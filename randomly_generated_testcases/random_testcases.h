#ifndef AUTOMATIC_BARGAIN_HUNTING_RANDOM_TESTCASES_H
#define AUTOMATIC_BARGAIN_HUNTING_RANDOM_TESTCASES_H
#include "../src/data_manager/data_manager.h"

void print_item(Item_Type* item);
void print_store_test(Store_Type* store);
void print_all_stores_test(Store_Type* store);
void print_all_items(Item_Type** items);

Store_Type* generate_stores_sorted(int store_len, int list_len);
Store_Type* generate_stores_unsorted(int store_len, int list_len);
void free_all_stores_test(Store_Type* store);

#endif //AUTOMATIC_BARGAIN_HUNTING_RANDOM_TESTCASES_H
