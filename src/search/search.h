#ifndef AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#define AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#include "../data_manager/data_manager.h"
void free_query(Item_Type** query_result);
Item_Type** find_items(const char* query, Item_Type** items, size_t size, size_t* size_output);
#endif //AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
