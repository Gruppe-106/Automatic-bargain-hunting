// Includes struct as well as 'public' functions, private prototypes should be in here.
#include "data_manager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "C:\Users\madsh\CLionProjects\Automatic-bargain-hunting\libs\parson\parson.h"

// Private protoypes:
Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic);
void free_item(Item_Type* item);
void free_items(Item_Type* items, int item_count);

// Definitions:
/**
 * @brief Creates an item from a bunch of parameters. Remember to free this item.
 * @param name string, name of the item
 * @param price double, price of the item
 * @param unit_size int, amount of units in the item
 * @param unit Unit_Type, type of the unit in the item
 * @param organic _Bool, is the item organic, or not
 * @return Memory allocated item, containing all parameters.
 */
Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic)
{
    Item_Type* item  = (Item_Type*)malloc(sizeof(Item_Type));
    item->name       = (char*)malloc(strlen(name) * sizeof(char));
    item->price      = price;
    item->unit_size  = unit_size;
    item->unit       = unit;
    item->organic    = organic;

    /* Parson demands that memcpy is used instead of strcpy*/
    memcpy(item->name, name, strlen(name) + 1);

    return item;
}

/**
 * @brief Frees the item along with the name
 * @param item Item_Type, item to be freed.
 */
void free_item(Item_Type* item)
{
    free(item->name);
    free(item);
}

/**
 * @brief Frees an array of items, with length item_count
 * @param items ptr, pointer to the first index value
 * @param item_count int, amount of items in the array
 */
void free_items(Item_Type* items, int item_count)
{
    for (int i = 0; i < item_count; ++i) {
        free_item(&items[i]);
    }
}

Item_Type* create_items()
{
    /* Parses the file*/
    JSON_Value *salling = json_parse_file(file_name);

    /* JSON variables */
    JSON_Array *clearences,
               *product_list;
    JSON_Object *current_clearence,
                *current_offer,
                *current_store;

    /* Local variables */
    Item_Type **items;
    int offer_size,
        num_of_products,
        current_index = 0,
        clearences_size;

    /* If file has been parsed unsuccessfully */
    if (json_value_get_type(salling) != JSONArray)
    {
        printf("Can't find file");
        exit(EXIT_FAILURE);
    }



    /* Get lvl 1 arrays meaning the clearences arrays */
    clearences      = json_value_get_array (salling);
    clearences_size = json_array_get_count (clearences);


    /* Get amount of items */
    for (int i = 0; i < clearences_size; i++)
    {
        current_clearence = json_array_get_object(clearences, i);
        product_list      = json_object_get_array(current_clearence, "clearances");
        offer_size        = json_array_get_count(product_list);
        num_of_products   += offer_size;
    }

    /* Get items */
    for (int i = 0; i < clearences_size; ++i) {

    }

    /* Dynamically allocate for array of items */
    items = (Item_Type**)malloc(sizeof(Item_Type) * num_of_products);

    for (int i = 0; i < clearences_size; i++)
    {
        /* Get the i'th clearence array*/
        current_clearence = json_array_get_object(clearences, i);

        /* Get the inside of the i'th clearance array*/
        product_list      = json_object_get_array(current_clearence, "clearances");
        offer_size        = json_array_get_count (product_list);

        /* Get the current store */
        current_store    =  json_object_get_object(current_clearence, "store");

        for (int j = 0; j < offer_size; j++)
        {
            /* Get the i'th clearance array's inside objects */
            current_offer = json_array_get_object(product_list, j);

            /* Reads the objetcs and creates a new product */
            items[current_index] = create_item(
                    json_object_dotget_string(current_offer,"product.description"),
                    json_object_get_string(current_store, "brand"),
                    json_object_dotget_number(current_offer,"offer.newPrice"),
                    json_object_dotget_number(current_offer,"offer.originalPrice"),
                    json_object_dotget_number(current_offer,"offer.percentDiscount"));
            current_index++;
        }



    }


    print_products (items, num_of_products);
    free_products  (items, num_of_products);

    /* Frees the salling JSON value */
    json_value_free(salling);
}