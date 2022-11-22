#include "../libs/utility/utility.h"
#include "../libs/utility/utility.c"
#include "../libs/parson/parson.h"
#include "../libs/parson/parson.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
	KILOGRAM,
	EACH,
	UNKNOWN,
} Unit_Type;
Unit_Type find_unit(const char* name);

typedef struct item
{
	char *name;
	bool organic;
	Unit_Type unit;
} item;
item *create_item  (const char *name,  bool organic, Unit_Type unit);

void example(char *file);
void free_products(item **products, int num_of_products);
void print_products(item **products, int num_of_products);

bool is_organic    (const char *name);


int main(int argc, char *argv[])
{
	example(argv[1]);
	return 0;
}

/**
 * @brief Create a item object
 *
 * @param name  name of the product
 * @return item*
 */
item *create_item(const char *name, bool organic, Unit_Type unit)
{
	item *product = (item *)parson_malloc(sizeof(item));
	product->name    = (char* )malloc(strlen(name) * sizeof(char));
	product->organic = organic;
	product->unit    = unit;

	/* Parson demands that memcpy is used instead of strcpy*/
	memcpy(product->name, name, strlen(name) + 1);

	return product;
}

/**
 * @brief find the unit for the current item
 * 
 * @param name name to process
 * @return Unit_Type
 */
Unit_Type find_unit(const char* name)
{
	Unit_Type product_unit;

	if(strcmp(toLower(name), "kg") == 0){
		product_unit = KILOGRAM;
	} else {
		product_unit = EACH;
	}

	return product_unit;
}

/**
 * @brief Checks if product is organic
 *
 * @param name name of the product
 * @return true
 * @return false
 */
bool is_organic(const char *name)
{

	/* Creates a cpy, needed since strtok is destructive */
	char *cpy = (char *)malloc(sizeof(char) * strlen(name));
	memcpy(cpy, name, strlen(name) + 1);

	char *delimiters = " ";
	char *token = strtok(cpy, delimiters);

	int flag = false;

	while (token)
	{

		if (strcmp(toLower(token), "oeko") == 0 || strcmp(toLower(token), "oekologisk") == 0)
		{
			flag = true;

			break;
		}
		token = strtok(NULL, delimiters);
	}
	free(cpy);
	return flag;
}

/**
 * @brief Frees item
 *
 * @param products        array of item structs
 * @param num_of_products number of items
 */
void free_products(item **products, int num_of_products)
{

	for (int i = 0; i < num_of_products; i++)
	{
		free(products[i]->name);
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
void print_products(item **products, int num_of_products)
{
	for (int i = 0; i < num_of_products; i++)
	{
		printf("Product name: %s\n\t- Organic: %s\n\t- Unit: %s\n",
        toLower(products[i]->name),
		products[i]->organic ? "Yes": "No",
		products[i]->unit ? "KG" : "EACH");
	}

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
	JSON_Object *current_clearence, *current_offer;
	item **products;

	int clearences_size;
	int offer_size;
	int num_of_products;
	int current_index = 0;
	char *name;
	

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
	clearences = json_value_get_array(salling);
	clearences_size = json_array_get_count(clearences);

	/* Get amount of products */
	for (int i = 0; i < clearences_size; i++)
	{
		current_clearence = json_array_get_object(clearences, i);
		product_list = json_object_get_array(current_clearence, "clearances");
		offer_size = json_array_get_count(product_list);
		num_of_products += offer_size;
	}

	/* Dynamically allocate for array of products */
	products = (item **)malloc(sizeof(item) * num_of_products);

	for (int i = 0; i < clearences_size; i++)
	{
		/* Get the i'th clearence array*/
		current_clearence = json_array_get_object(clearences, i);

		/* Get the inside of the i'th clearance array*/
		product_list = json_object_get_array(current_clearence, "clearances");
   		offer_size    = json_array_get_count(product_list);

		for (int j = 0; j < offer_size; j++)
		{
			/* Get the i'th clearance array's inside objects */
			current_offer = json_array_get_object(product_list, j);

			/* Reads the objetcs and creates a new product */
			products[current_index] = create_item(
			    json_object_dotget_string(current_offer,"product.description"),
				is_organic(json_object_dotget_string(current_offer,"product.description")),
				find_unit(json_object_dotget_string(current_offer,"offer.stockUnit")));
			current_index++;
			// printf("%d\n",current_index);
		}
	}

	print_products (products,num_of_products);
	free_products  (products,num_of_products);

	/* Frees the salling JSON value */
	json_value_free(salling);
}
