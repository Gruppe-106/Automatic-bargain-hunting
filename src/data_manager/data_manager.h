#ifndef AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#define AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#include "../../libs/parson/parson.h"

typedef enum {
    GRAM,
    KILOGRAM,
    LITER,
    MILLILITER,
    EACH,
} Unit_Type;

typedef struct item {
    char* name;
    double price;
    int unit_size;
    Unit_Type unit;
    _Bool organic;
} Item_Type;

typedef struct store {
    char* name;
    Item_Type** items;
    size_t item_amount;
    double total_price;
    struct store* next_node;
} Store_Type;

void updates_stores(JSON_Value *json, Store_Type** all_stores);
void free_stores(Store_Type* all_stores);
//Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic);
#endif //AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
