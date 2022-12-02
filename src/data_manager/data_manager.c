/*Includes struct as well as 'public' functions, private prototypes should be in here.*/

/* Standard libraries */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* Custom ibraries */
#include "data_manager.h"
#include "../util/string_utility.h"
#include "../util/unit_type_conversion.h"
#include "../util/store_utility.h"

//Prototypes
Item_Type* create_item(char* name, double price, double unit_size, Unit_Type unit, _Bool organic);
Item_Type* create_item_from_salling(JSON_Object *json_item);
Item_Type* create_item_from_rema(JSON_Object *json_item);

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
    store->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    memcpy(store->name, name, strlen(name));

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

Item_Type** allocate_or_reallocate_items(Store_Type* store, size_t product_amount) {
    Item_Type **items;
    if (store->item_amount == 0) {
        //Allocated space needed for all items
        items = (Item_Type**) calloc(product_amount, sizeof(Item_Type*));
        store->item_amount = product_amount;
    } else {
        //If is not zero more space is needed to be able to store new items
        items = store->items;
        store->item_amount += product_amount;
        //Reallocate space to fit new items and old items
        items = (Item_Type**) realloc(items, store->item_amount * sizeof(Item_Type*));
    }
    return items;
}

/**
 * @brief Converts a JSON object to the Store_Type & assigns it to current list of all stores \n
 * Should only be used for json from Rema-1000
 * @param json json to convert
 * @param all_stores Store_type ptr, all stores can be NULL
 */
void json_to_store_rema(JSON_Value *json, Store_Type** all_stores) {
    //Add or get the ptr of store Rema-1000
    Store_Type* rema = create_and_add_store("rema-1000", all_stores);

    //Get the product array & the amount of product_list from the json
    JSON_Array *product_list = json_value_get_array (json);
    size_t product_amount = json_array_get_count (product_list);

    //Get the current last last_index of items in the Rema Store_Type
    size_t last_index = rema->item_amount;

    Item_Type** items = allocate_or_reallocate_items(rema, product_amount);
    for (int i = 0; i < product_amount; ++i) {
        //Get next product in the json array
        JSON_Object *cur_item = json_array_get_object(product_list, i);
        //Create item
        Item_Type* item = create_item_from_rema(cur_item);

        //Add item to the items list, if not NULL
        if (item != NULL) {
            items[i + last_index] = item;
        }
    }
    //Update the Store_Type items list
    rema->items = items;
}

/**
 * @brief Converts a JSON object to the Store_Type & assigns it to current list of all stores\n
 * Should only be used for json from Salling Clearances
 * @param json json to convert
 * @param all_stores Store_type ptr, all stores can be NULL
 */
void json_to_stores_salling_clearances(JSON_Value *json, Store_Type** all_stores) {
    //Get first layer of the JSON
    JSON_Array *clearances = json_value_get_array (json);
    size_t clearances_size = json_array_get_count (clearances);

    for (int i = 0; i < clearances_size; ++i) {
        JSON_Object *current_clearances = json_array_get_object(clearances, i);
        //Get product list and the amount of products
        JSON_Array *product_list   = json_object_get_array(current_clearances, "clearances");
        size_t      product_amount = json_array_get_count(product_list);
        //Get brand name of store
        JSON_Object *store_list    = json_object_get_object(current_clearances, "store");
        char*        name          = (char*) json_object_get_string(store_list, "brand");

        //Get or create store if it doesn't exist
        Store_Type* store = create_and_add_store(name, all_stores);
        if (store != NULL) {
            size_t last_index = store->item_amount;
            //Allocate or reallocate space for new items and get back last_index of new item
            Item_Type **items = allocate_or_reallocate_items(store, product_amount);

            //Loop through all new items and add them to list of items
            for (int j = 0; j < product_amount; ++j) {
                //Get current item from JSON
                JSON_Object *json_item    = json_array_get_object(product_list, j);
                //Create an item based on that data
                Item_Type *item = create_item_from_salling(json_item);
                //If item is not null add it to the list
                if (item != NULL) {
                    items[j + last_index] = item;
                }
            }
            //Reassign pointer to items list to the store
            store->items = items;
        }
    }
}

/**
 * @brief Injection point should take in a json and the list of all store \n
 * This function should be all you need to call from this file \n
 * This function should dynamically allocate store and items as needed
 * @param json json to convert
 * @param all_stores Store_type ptr, all stores can be NULL
 * @param type Valid_Stores_Type, Enum of a valid store
 */
void update_stores(JSON_Value *json, Store_Type** all_stores, Valid_Stores_Enum type) {
    // Check if JSON is Not Null
    if (json == NULL) {
        printf("[updates_stores] JSON is a NullPointerReference");
        exit(EXIT_FAILURE);
    }

    //Call json to store converter depending on type of store
    switch (type) {
        case SALLING_CLEARANCES:
            json_to_stores_salling_clearances(json, all_stores);
            break;
        case REMA:
            json_to_store_rema(json, all_stores);
            break;
        default:
            return;
    }

    //Free JSON from memory
    json_value_free(json);
}

/* ================================================== *
 *           Create item from vars and JSON           *
 * ================================================== */

/**
 * @brief Creates an item from a bunch of parameters. Remember to free this item.
 * @param name const char*, name of the item
 * @param price double, price of the item
 * @param unit_size int, amount of units in the item
 * @param unit Unit_Type, type of the unit in the item
 * @param organic _Bool, is the item organic, or not
 * @return Memory allocated item, containing all parameters.
 */
Item_Type* create_item(char* name, double price, double unit_size, Unit_Type unit, _Bool organic) {
    //Allocate item and name and assign all parameters
    Item_Type* item  = (Item_Type*)malloc(sizeof(Item_Type));
    item->name       = (char*) malloc(strlen(name) * (sizeof(char)+1));
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
 * Creates a Item_Type ptr from a Salling JSON
 * @param json_item JSON_Object ptr, JSON item to get data from
 * @return Item_Type ptr
 */
Item_Type* create_item_from_salling(JSON_Object *json_item) {
    if (json_item == NULL) return NULL;
    //Get the two JSON Objects that's within the JSON item object
    JSON_Object *item_offer   = json_object_get_object(json_item, "offer");
    JSON_Object *item_product = json_object_get_object(json_item, "product");

    //Get all useful parameters of the JSON item
    char     *name      = (char*) json_object_get_string(item_product, "description");
    double    price     = json_object_get_number(item_offer, "newPrice");
    double    unit_size = json_object_get_number(item_offer, "stock");
    Unit_Type unit      = str_to_unit_type((char *) json_object_get_string(item_offer, "stockUnit"));
    _Bool     organic   = str_contains_str((char *) name, "oeko", false) != -1 || str_contains_str((char *) name, "oekologisk",false) != -1;

    //Create item and return the ptr
    return create_item(name, price, unit_size, unit, organic);
}

/**
 * Creates a Item_Type ptr from a Rema JSON
 * @param json_item JSON_Object ptr, JSON item to get data from
 * @return Item_Type ptr
 */
Item_Type* create_item_from_rema(JSON_Object *json_item) {
    if (json_item == NULL) return NULL;

    //Get all useful parameters of the JSON item
    char     *name      = (char*) json_object_get_string(json_item, "name");
    double    price     = json_object_get_number(json_item, "price");
    double    unit_size = json_object_get_number(json_item, "unit_size");
    Unit_Type unit      = str_to_unit_type((char *) json_object_get_string(json_item, "unit_type"));
    _Bool     organic   = str_contains_str((char *) name, "oeko", false) != -1;

    //Create item and return the ptr
    return create_item(name, price, unit_size, unit, organic);
}

