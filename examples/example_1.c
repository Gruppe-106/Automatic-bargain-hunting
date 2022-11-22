#include "../libs/parson/parson.h"
#include "../libs/parson/parson.c"
#include <stdio.h>
#include <stdlib.h>


typedef struct item{
    char*       name;
    char*       store;
    double      newPrice;
    double      originalPrice;
    double      percentDiscount;
} item;

void example       (char *file);
void free_products (item **products, int num_of_products);
void print_products(item **products, int num_of_products);
item *create_item  (const char *name,const char *store, double newPrice, double originalPrice, double percentDiscount);


int main(int argc, char *argv[])
{
    example(argv[1]);
    return 0;
}


/**
 * @brief Create a item object
 *
 * @param name              name of the product
 * @param newPrice          new price of the product
 * @param originalPrice     original price of the product
 * @param percentDiscount   persent of the original price
 * @return item*
 */
item *create_item(const char *name, const char *store, double newPrice, double originalPrice, double percentDiscount){
    item* product = (item*)parson_malloc(sizeof(item));

    product->name            = malloc(strlen(name)*sizeof(char));
    product->store           = malloc(strlen(store)*sizeof(char));
    product->newPrice        = newPrice;
    product->originalPrice   = originalPrice;
    product->percentDiscount = percentDiscount;
   
    /* Parson demands that memcpy is used instead of strcpy*/
    memcpy(product->name,  name, strlen(name)+1);
    memcpy(product->store, store,strlen(store)+1);

    return product;
}

/**
 * @brief example function
 *
 */
void example(char *file_name)
{
    /* Parses the file*/
    JSON_Value *salling = json_parse_file(file_name);

    JSON_Array *clearences, *product_list;
    JSON_Object *current_clearence, *current_offer, *current_store;
    item **products;

    int clearences_size;
    int offer_size;
    int num_of_products;
    int current_index = 0;

    /* If file has been parsed unsuccessfully */
    if (json_value_get_type(salling) != JSONArray)
    {
        printf("Can't find file");
        exit(EXIT_FAILURE);
    }

    /**
     * salling JSON has the format
     * clearances": [
            {
                "offer": {
                    ...
                },
                "product": {
                    ...
                }
            },
            ...
     *  ],
     *  "store": {
     *     ...
     *  },
     *  clearances": [
     *     ...
     *  ]
     */

    /* Get lvl 1 arrays meaning the clearences arrays */
    clearences      = json_value_get_array (salling);
    clearences_size = json_array_get_count (clearences);
      

    /* Get amount of products */
    for (int i = 0; i < clearences_size; i++)
    {
        current_clearence = json_array_get_object(clearences, i);
        product_list      = json_object_get_array(current_clearence, "clearances");
        offer_size        = json_array_get_count(product_list);
        num_of_products   += offer_size;

    }

    /* Dynamically allocate for array of products */
    products = (item**)malloc(sizeof(item)*num_of_products);

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

    /* Frees the salling JSON value */
    json_value_free(salling);
}


/**
 * @brief Frees item
 *
 * @param products        array of item structs
 * @param num_of_products number of items
 */
void free_products(item **products, int num_of_products){

    for (int i = 0; i < num_of_products; i++){
        free(products[i]->name);
        free(products[i]->store);
        free(products[i]);
    }

    free(products);

}

/**
 * @brief prints the items to the console
 *
 * @param products        array of item structs
 * @param num_of_products number of items
 */
void print_products(item **products, int num_of_products){

    for (int i = 0; i < num_of_products; i++){
        printf("Product name: %s\n\t- Store: %s\n\t- New price: %.2lf\n\t- Original price: %.2lf\n\t- Percent off: %.2lf\n",
            products[i]->name,
            products[i]->store,
            products[i]->newPrice,
            products[i]->originalPrice,
            products[i]->percentDiscount);
    }

}

