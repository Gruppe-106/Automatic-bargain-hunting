#ifndef AUTOMATIC_BARGAIN_HUNTING_NODE_HANDLER_H
#define AUTOMATIC_BARGAIN_HUNTING_NODE_HANDLER_H
#include "../data_manager/data_manager.h"

void free_item(Item_Type* item);
void free_items(Item_Type** items, size_t item_amount);
void free_store(Store_Type* store);
void free_stores(Store_Type* all_stores);

#endif //AUTOMATIC_BARGAIN_HUNTING_NODE_HANDLER_H
