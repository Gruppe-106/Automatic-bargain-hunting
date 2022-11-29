#ifndef AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#define AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
#include "../data_manager/data_manager.h"
Item_Type** find_items_in_items_by_str(char* query, Item_Type** items, size_t len, int* size_output);
char** tokenize(const char* string, int* words_length_output);
#endif //AUTOMATIC_BARGAIN_HUNTING_SEARCH_H
