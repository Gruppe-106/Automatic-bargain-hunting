#include "../../Automatic-bargain-hunting/randomly_generated_testcases/random_testcases.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../src/util/string_utility.h"

#define ITEM_NAMES_LEN 24
#define PRICE_RANGE_LOWER 1
#define PRICE_RANGE_UPPER 1000
#define UNIT_RANGE_LOWER 1
#define UNIT_RANGE_UPPER 100
#define STORE_NAMES_LEN 5

/* PROTOTYPES */
Item_Type* generate_item(char** item_names, char** store_names);
Item_Type** generate_items(int len, char** item_names, char** store_names);
Store_Type* generate_stores_with_lists(int store_len, int list_len);
void free_item_test(Item_Type* item);
void free_items(Item_Type** items);
Store_Type* generate_store(int item_len, Store_Type* next_node, char** item_names, char** store_names);
void free_store_test(Store_Type* store);
void free_all_stores_test(Store_Type* store);
void print_item(Item_Type* item);
void print_store_test(Store_Type* store);
void print_all_stores_test(Store_Type* store);
void print_all_items(Item_Type** items);

/* DEFINITIONS */
Store_Type* generate_stores_with_lists(int store_len, int list_len)
{
    char* item_names[ITEM_NAMES_LEN] =
            {
                    "KAMSTEG SALLING oeKO",
                    "KINDER CHOCO 5-PAK",
                    "SVINEKaeBER SLAGTEREN",
                    "oeKOLOGISK MaeLK NATURMaeLK",
                    "VEGGIE NUDELRET DGS",
                    "SPARERIBS SLAGTEREN",
                    "GRaeSK GYROS SLAGTEREN",
                    "FARSBRoeD SLAGTERMEST",
                    "MINIKUGLER GALBANI",
                    "DGR. SOLSIKKE DET GODE",
                    "JORDBaeR YOGHURT YOGGI",
                    "KALVE RIBS BOOST",
                    "BURGERBoeFFER LUDVIG",
                    "BACON-PEBER 300 G",
                    "KOKOS SKYR YOG. CHEASY",
                    "oeKO SKUMMETMaeLK NATURMaeLK",
                    "KYLLINGE BACON SALLING",
                    "ASIAN PASTA TPK",
                    "TAPAS SALAMI AALBaeK",
                    "SANDW. SKI/OST BY KAVSMAN",
                    "ENERGISE SMOOTH INNOCENT",
                    "CHIA M/MANGO TPK",
                    "SANDW. TOM/MOZ BY KAVSMAN",
                    "PASTA SPICY SALLING oeKO",
            };

    char* store_names[STORE_NAMES_LEN] =
            {
                    "foetex",
                    "netto",
                    "lidl",
                    "bilka",
                    "rema1000",
            };
    for (int i = 0; i < ITEM_NAMES_LEN; ++i) {
        str_to_lower(&item_names[i]);
    }
    srand(time(NULL));
    Store_Type* next_store = NULL;
    for (int i = 0; i < store_len; ++i) {
        next_store = generate_store(list_len, next_store, item_names, store_names);
    }
    return next_store;
}
Store_Type* generate_store(int item_len, Store_Type* next_node, char** item_names, char** store_names)
{
    int store_number = rand() % STORE_NAMES_LEN;
    Store_Type* store = (Store_Type*) malloc(sizeof (Store_Type));
    store->name = (char*) malloc(strlen(store_names[store_number]));
    strcpy(store->name, store_names[store_number]);
    store->items = generate_items(item_len, item_names, store_names);
    store->next_node = next_node;
    store->total_price = -1;
    return store;
}
Item_Type** generate_items(int len, char** item_names, char** store_names)
{
    Item_Type** items = (Item_Type**)malloc(sizeof(Item_Type) * (len + 1));
    for (int i = 0; i < len; ++i) {
        items[i] = generate_item(item_names, store_names);
    }
    items[len] = NULL;
    return items;
}
Item_Type* generate_item(char** item_names, char** store_names)
{

    int item_number_rand = rand() % ITEM_NAMES_LEN;

    Item_Type* item = (Item_Type*)malloc(sizeof(Item_Type));
    item->name = malloc(strlen(item_names[item_number_rand]) * sizeof(char)); // Remember to free
    memcpy(item->name, item_names[item_number_rand], strlen(item_names[item_number_rand]) + 1); // Maybe use memccpy
    item->organic = rand() % 2;
    item->price = rand() % ((PRICE_RANGE_UPPER + 1) - PRICE_RANGE_LOWER) + PRICE_RANGE_LOWER; // Includes top range and lower range
    item->unit = rand() % 5;
    item->unit_size = rand() % ((UNIT_RANGE_UPPER + 1) - UNIT_RANGE_LOWER) + UNIT_RANGE_LOWER; // Includes top range and lower range

    return item;
}

void free_item_test(Item_Type* item)
{
    free(item->name);
    free(item);
}
void free_items(Item_Type** items)
{
    int i = 0;
    Item_Type* item = items[i];
    while (item != NULL)
    {
        free_item_test(item);
        ++i;
        item = items[i];
    }
    free(items);
}
void free_store_test(Store_Type* store)
{
    free_items(store->items);
    free(store->name);
    free(store);
}
void free_all_stores_test(Store_Type* store)
{
    while (store != NULL)
    {
        Store_Type* next_store = store->next_node;
        free_store_test(store);
        store = next_store;
    }
}
void print_item(Item_Type* item)
{
    printf("NAME: %s\n", item->name);
    printf("PRICE: %lf\n", item->price);
    printf("ORGANIC: %d\n", item->organic);
    printf("UNIT_SIZE: %d\n", item->unit_size);
    printf("UNIT: %d\n", item->unit);
}
void print_all_items(Item_Type** items)
{
    int i = 0;
    Item_Type* item = items[0];
    while (item != NULL)
    {
        print_item(item);
        printf("\n");
        ++i;
        item = items[i];
    }
}
void print_store_test(Store_Type* store)
{
    printf("STORE NAME: %s", store->name);
    print_all_items(store->items);
}
void print_all_stores_test(Store_Type* store)
{
    while (store != NULL)
    {
        print_store_test(store);
        store = store->next_node;
    }
}