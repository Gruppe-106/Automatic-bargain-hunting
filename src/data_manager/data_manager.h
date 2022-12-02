#ifndef AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#define AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#include "../../libs/parson/parson.h"

typedef enum {
    GRAM,
    KILOGRAM,
    LITER,
    MILLILITER,
    CENTILITER,
    EACH,
    METER,
    SET
} Unit_Type;

typedef struct item {
    char* name;
    double price;
    double unit_size;
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

void update_stores(JSON_Value *json, Store_Type** all_stores, char* store_name);
#define append_json_data(json, all_stores) update_stores(json, all_stores, #json)

void print_store(Store_Type* store);
#endif //AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
