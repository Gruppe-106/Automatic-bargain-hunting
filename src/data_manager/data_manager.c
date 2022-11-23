// Includes struct as well as 'public' functions, private prototypes should be in here.
#include "data_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../util/string_utility.h"

//Prototypes
Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic);

typedef struct {
    const char *name;
    JSON_Array *product_list;
    size_t product_amount;
} Pre_Store_Type;

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
_Bool create_and_add_store(const char* name, Store_Type** all_stores) {
    //Loop through all_stores nodes until an empty is found or one with same name is found
    Store_Type *next = *all_stores;
    if (next != NULL) {
        //It annoys me to do it like this, but only way I could find that worked
        //If name is the same return, as store is already assigned
        if (strcmp(next->name, name) == 0) return false;
        do {
            //Get next node
            if (next->next_node != NULL) next = next->next_node;
            //If name is the same return, as store is already assigned
            if (strcmp(next->name, name) == 0) return false;
        } while (next->next_node != NULL);
    }
    //Allocate store
    Store_Type* store = (Store_Type*) malloc(sizeof(Store_Type));

    //Allocate and assign name
    store->name = (char*) malloc(strlen(name) * sizeof(char));
    memcpy(store->name, name, strlen(name) + 1);

    //Set rest to empty values
    store->next_node   = NULL;
    store->items       = NULL;
    store->total_price = 0;

    //If all_stores is null set it to new store
    if (*all_stores == NULL) {
        *all_stores = store;
        return true;
    }
    //Assign next free node to newly allocated store
    next->next_node = store;
    return true;
}

/**
 * @brief Injection point should take in a json and the list of all store \n
 * This function should be all you need to call from this file \n
 * This function should dynamically allocate store and items as needed
 * @param json json to convert
 * @param all_stores Store_type ptr, all stores can be NULL
 */
void updates_stores(JSON_Value *json, Store_Type** all_stores) {
    /* Check if JSON is Not Null */
    if (json == NULL) {
        printf("[updates_stores] JSON is a NullPointerReference");
        exit(EXIT_FAILURE);
    }

    //Get first layer of the JSON
    JSON_Array *clearances = json_value_get_array (json);
    size_t clearances_size = json_array_get_count (clearances);

    //Get all stores and they product list
    Pre_Store_Type existing_stores[clearances_size];
    for (int store = 0; store < clearances_size; ++store) {
        JSON_Object *current_clearances = json_array_get_object(clearances, store);
        //Get product list and the amount of products
        existing_stores[store].product_list   = json_object_get_array(current_clearances, "clearances");
        existing_stores[store].product_amount = json_array_get_count(existing_stores[store].product_list);
        //Get brand name of store
        JSON_Object *store_list     = json_object_get_object(current_clearances, "store");
        existing_stores[store].name = json_object_get_string(store_list, "brand");

        create_and_add_store(existing_stores[store].name, all_stores);
    }

    for (Store_Type *next = *all_stores; next != NULL ; next = next->next_node) {
        size_t item_count = 0;
        for (int i = 0; i < clearances_size; ++i) {
            if (strcmp(existing_stores->name, next->name) == 0) {
                item_count += existing_stores->product_amount;
            }
        }

        next->items = (Item_Type**) malloc(sizeof(Item_Type) * (item_count + 1));
        Item_Type *items = *next->items;
        size_t items_index = 0;
        for (int i = 0; i < clearances_size; ++i) {
            if (strcmp(existing_stores->name, next->name) == 0) {
                for (int j = 0; j < existing_stores[i].product_amount; ++j, ++items_index) {
                    JSON_Object *json_item = json_array_get_object(existing_stores[i].product_list, j);
                    JSON_Object *item_offer = json_object_get_object(json_item, "offer");
                    JSON_Object *item_product = json_object_get_object(json_item, "product");

                    const char *name = json_object_get_string(item_product, "description");
                    double price = json_object_get_number(item_offer, "newPrice");
                    int unit_size = (int) json_object_get_number(item_offer, "stock");
                    Unit_Type unit = str_to_unit_type((char *) json_object_get_string(item_offer, "stockUnit"));
                    _Bool organic = str_contains_string((char *) name, "oeko", false) != -1;

                    Item_Type *item = create_item((char *) name, price, unit_size, unit, organic);
                    next->items[items_index] = item;
                }
            }
            next->items[items_index + 1] = NULL;
        }
    }

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
    item->name       = (char*)malloc(strlen(name) * sizeof(char));
    item->price      = price;
    item->unit_size  = unit_size;
    item->unit       = unit;
    item->organic    = organic;

    /* Copy string using memcpy*/
    memcpy(item->name, name, strlen(name) + 1);

    return item;
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
    free(store->name);
    free_items(store->items);
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

/*
Item_Type* create_items(char *file_name)
{
    JSON_Value *salling = json_parse_file(file_name);

    JSON_Array *clearences, *product_list;
    JSON_Object *current_clearence, *current_offer, *current_store;
    item **products;

    int clearences_size;
    int offer_size;
    int num_of_products;
    int current_index = 0;

    //Get lvl 1 arrays meaning the clearences arrays
    clearences      = json_value_get_array (salling);
    clearences_size = json_array_get_count (clearences);


    //Get amount of products
    for (int i = 0; i < clearences_size; i++)
    {
        current_clearence = json_array_get_object(clearences, i);
        product_list      = json_object_get_array(current_clearence, "clearances");
        offer_size        = json_array_get_count(product_list);
        num_of_products   += offer_size;

    }

    // Dynamically allocate for array of products
    products = (Item_Type**)malloc(sizeof(Item_Type)*num_of_products);

    for (int i = 0; i < clearences_size; i++)
    {
        // Get the i'th clearence array
        current_clearence = json_array_get_object(clearences, i);

        // Get the inside of the i'th clearance array
        product_list      = json_object_get_array(current_clearence, "clearances");
        offer_size        = json_array_get_count (product_list);

        // Get the current store
        current_store    =  json_object_get_object(current_clearence, "store");

        for (int j = 0; j < offer_size; j++)
        {
            // Get the i'th clearance array's inside objects
            current_offer = json_array_get_object(product_list, j);

            // Reads the objetcs and creates a new product
            products[current_index] = create_item(
                    json_object_dotget_string(current_offer,"product.description"),
                    json_object_get_string(current_store, "brand"),
                    json_object_dotget_number(current_offer,"offer.newPrice"),
                    json_object_dotget_number(current_offer,"offer.originalPrice"),
                    json_object_dotget_number(current_offer,"offer.percentDiscount"));
            current_index++;
        }



    }


    print_products (products,num_of_products);
    free_products  (products,num_of_products);

    // Frees the salling JSON value
    json_value_free(salling);
}
*/

void test() {
    JSON_Value *json = json_parse_file("data/salling.json");
    Store_Type* all_stores = NULL;
    updates_stores(json, &all_stores);
    Store_Type *next = all_stores;
    puts("test");
    while(1) {
        puts(next->name);
        if (next->next_node == NULL)
            break;
        next = next->next_node;
    }
    free_stores(all_stores);
}