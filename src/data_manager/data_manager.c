// Includes struct as well as 'public' functions, private prototypes should be in here.
#include "data_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../util/string_utility.h"

//Prototypes
Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic);
Item_Type* create_item_from_json(JSON_Object *json_item);

//Used for temporary organization of data in before being parsed to Item_Type struct in Store_Type
typedef struct {
    char *name;
    Store_Type *store;
    size_t product_amount;
} Pre_Store_Type;

/**
 * Converts a string to a Unit_Type if exist
 * @param str char*, string to check
 * @return Unit_Type, if applicable otherwise -1
 */
Unit_Type str_to_unit_type(char* str) {
    str_to_lower(&str);
    if (strcmp(str, "g") == 0)
        return GRAM;
    else if (strcmp(str, "kg") == 0)
        return KILOGRAM;
    else if (strcmp(str, "l") == 0)
        return LITER;
    else if (strcmp(str, "ml") == 0)
        return MILLILITER;
    else if (strcmp(str, "each") == 0)
        return EACH;
    return -1;
}

/* ================================================== *
 *       Create and/or update store linked list       *
 * ================================================== */

/**
 * Allocates and assigns a Store_Type with empty and name of param name
 * @param name char*, name of store
 * @param all_stores Store_Type ptr, list of all stores
 */
Store_Type* create_and_add_store(const char* name, Store_Type** all_stores) {
    //Loop through all_stores nodes until an empty is found or one with same name is found
    Store_Type *next = *all_stores;
    if (next != NULL) {
        //It annoys me to do it like this, but only way I could find that worked
        //If name is the same return, as store is already assigned
        if (strcmp(next->name, name) == 0) return next;
        do {
            //Get next node
            if (next->next_node != NULL) next = next->next_node;
            //If name is the same return, as store is already assigned
            if (strcmp(next->name, name) == 0) return next;
        } while (next->next_node != NULL);
    }
    //Allocate store
    Store_Type* store = (Store_Type*) malloc(sizeof(Store_Type));

    //Allocate and assign name
    store->name = (char*) malloc(strlen(name) * sizeof(char));
    memcpy(store->name, name, strlen(name) + 1);

    //Set rest to empty values
    store->next_node   = NULL;
    store->item_amount = 0;
    store->items       = NULL;
    store->total_price = 0;

    //If all_stores is null set it to new store
    if (*all_stores == NULL) {
        *all_stores = store;
        return *all_stores;
    }
    //Assign next free node to newly allocated store
    next->next_node = store;
    return store;
}

/**
 * @brief Injection point should take in a json and the list of all store \n
 * This function should be all you need to call from this file \n
 * This function should dynamically allocate store and items as needed
 * @param json json to convert
 * @param all_stores Store_type ptr, all stores can be NULL
 */
void updates_stores(JSON_Value *json, Store_Type** all_stores) {
    // Check if JSON is Not Null
    if (json == NULL) {
        printf("[updates_stores] JSON is a NullPointerReference");
        exit(EXIT_FAILURE);
    }

    //Get first layer of the JSON
    JSON_Array *clearances = json_value_get_array (json);
    size_t clearances_size = json_array_get_count (clearances);

    for (int i = 0; i < clearances_size; ++i) {
        JSON_Object *current_clearances = json_array_get_object(clearances, i);
        //Get product list and the amount of products
        JSON_Array *product_list   = json_object_get_array(current_clearances, "clearances");
        size_t      product_amount = json_array_get_count(product_list);
        //Get brand name of store
        JSON_Object *store_list     = json_object_get_object(current_clearances, "store");
        char*        name           = (char*) json_object_get_string(store_list, "brand");

        Item_Type **items;
        //Get or create store if it doesn't exist
        Store_Type* store = create_and_add_store(name, all_stores);
        if (store != NULL) {
            size_t index = 0;
            //If item amount is zero no items therefore memory isn't allocated
            if (store->item_amount == 0) {
                //Allocated space needed for all items
                items = (Item_Type**) calloc((product_amount), sizeof(Item_Type*));
                store->item_amount = product_amount;
            } else {
                //If is not zero more space is needed to be able to store new items
                items = store->items;
                index = store->item_amount;
                store->item_amount += product_amount;
                //Reallocate space to fit new items and old items
                items = (Item_Type**) realloc(items, store->item_amount * sizeof(Item_Type*));
            }

            //Loop through all new items and add them to list of items
            for (int j = 0; j < product_amount; ++j) {
                //Get current item from JSON
                JSON_Object *json_item    = json_array_get_object(product_list, j);
                //Create an item based on that data
                Item_Type *item = create_item_from_json(json_item);
                //If item is not null add it to the list
                if (item != NULL) {
                    items[j + index] = item;
                }
            }
            //Reassign pointer to items list to the store
            store->items = items;
        }
    }
    //Free JSON from memory
    json_value_free(json);
}

/**
 * @brief Creates an item from a bunch of parameters. Remember to free this item.
 * @param name const char*, name of the item
 * @param price double, price of the item
 * @param unit_size int, amount of units in the item
 * @param unit Unit_Type, type of the unit in the item
 * @param organic _Bool, is the item organic, or not
 * @return Memory allocated item, containing all parameters.
 */
Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic) {
    //Allocate item and name and assign all parameters
    Item_Type* item  = (Item_Type*)malloc(sizeof(Item_Type));
    item->name       = (char*)malloc(strlen(name) * (sizeof(char)+1));
    item->price      = price;
    item->unit_size  = unit_size;
    item->unit       = unit;
    item->organic    = organic;

    //Convert to lowercase and copy string using memcpy
    str_to_lower(&name);
    memcpy(item->name, name, strlen(name) + 1);

    return item;
}

/**
 * Creates a Item_Type ptr from a JSON item
 * @param json_item JSON_Object ptr, JSON item to get data from
 * @return Item_Type ptr
 */
Item_Type* create_item_from_json(JSON_Object *json_item) {
    if (json_item == NULL) return NULL;
    //Get the two JSON Objects that's within the JSON item object
    JSON_Object *item_offer   = json_object_get_object(json_item, "offer");
    JSON_Object *item_product = json_object_get_object(json_item, "product");

    //Get all useful parameters of the JSON item
    char     *name      = (char*) json_object_get_string(item_product, "description");
    double    price     = json_object_get_number(item_offer, "newPrice");
    int       unit_size = (int) json_object_get_number(item_offer, "stock");
    Unit_Type unit      = str_to_unit_type((char *) json_object_get_string(item_offer, "stockUnit"));
    _Bool     organic   = str_contains_str((char *) name, "oeko", false) != -1;

    //Create item and return the ptr
    return create_item(name, price, unit_size, unit, organic);

}

/* ================================================== *
 *      De-allocation of store and members within     *
 * ================================================== */

/**
 * @brief Frees the item along with the name
 * @param item Item_Type, item to be freed.
 */
void free_item(Item_Type* item) {
    free(item->name);
    free(item);
}

/**
 * @brief Frees an array of items, with length item_count
 * @param items ptr, pointer to the first index value
 * @param item_count int, amount of items in the array
 */
void free_items(Item_Type** items) {
    for (int i = 0; items[i] != NULL; ++i) {
        free_item(items[i]);
    }
}

/**
 * Frees a store and all it's members
 * @param store Store_Type ptr, ptr to store to free from heap
 */
void free_store(Store_Type* store) {
    free_items(store->items);
    free(store->name);
    free(store);
}

/**
 * @brief Free a node-based Store_Type list and everything within it
 * @param all_stores Store_Type ptr, for all stores to free
 */
void free_stores(Store_Type* all_stores) {
    if (all_stores == NULL) return;
    Store_Type* next = all_stores;
    while (next->next_node != NULL) {
        Store_Type *to_free = next;
        next = next->next_node;
        free_store(to_free);
    }
}

void test() {
    JSON_Value *json = json_parse_file("data/salling.json");
    Store_Type* all_stores = NULL;
    updates_stores(json, &all_stores);
    Store_Type *next = all_stores;
    for (int i = 0; i < next->item_amount; i++) {
        if((next->items[i]) == NULL) break;
        puts((*next->items[i]).name);
        printf("%lf \n\n", next->items[i]->price);
    }
    free_stores(all_stores);
}