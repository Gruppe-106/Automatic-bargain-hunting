#ifndef AUTOMATIC_BARGAIN_HUNTING_STRING_UTILITY_H
#define AUTOMATIC_BARGAIN_HUNTING_STRING_UTILITY_H
#include "../data_manager/data_manager.h"

int amount_of_stores(Store_Type *store);
void print_store(Store_Type* store);
void print_items(Item_Type **items, size_t items_len);

#endif //AUTOMATIC_BARGAIN_HUNTING_STRING_UTILITY_H
