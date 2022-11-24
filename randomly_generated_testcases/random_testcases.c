#include "../../Automatic-bargain-hunting/randomly_generated_testcases/random_testcases.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "../src/util/string_utility.h"
#include "../src/util/unit_type_conversion.h"


#define ITEM_NAMES_LEN 24
#define PRICE_RANGE_LOWER 1
#define PRICE_RANGE_UPPER 1000
#define UNIT_RANGE_LOWER 1
#define UNIT_RANGE_UPPER 100
#define STORE_NAMES_LEN 5

/* PROTOTYPES */
Store_Type *generate_store(int item_len, Store_Type *next_node, char **item_names, char **store_names);
Item_Type *generate_item(char **item_names);
Item_Type **generate_items(size_t len, char **item_names);

int comparator_price_asc(const void *p, const void *q);

void free_item_test(Item_Type *item);
void free_items(Item_Type **items, size_t len);
void free_store_test(Store_Type *store);

/* DEFINITIONS */
Store_Type *generate_stores_unsorted(int store_len, int list_len)
{
    char *item_names[ITEM_NAMES_LEN] =
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

    char *store_names[STORE_NAMES_LEN] =
        {
            "foetex",
            "netto",
            "lidl",
            "bilka",
            "rema1000",
        };

    for (int i = 0; i < ITEM_NAMES_LEN; ++i)
    {
        str_to_lower(&item_names[i]);
    }

    srand(time(NULL));
    Store_Type *next_store = NULL;
    for (int i = 0; i < store_len; ++i)
    {
        next_store = generate_store(list_len, next_store, item_names, store_names);
    }
    return next_store;
}
Store_Type *generate_stores_sorted(int store_len, int list_len)
{
    Store_Type *store = generate_stores_unsorted(store_len, list_len);
    Store_Type *og_store = store;
    while (store != NULL)
    {
        Item_Type** itemsTMP = store->items;
        qsort(store->items, store->item_amount, sizeof(Item_Type*), comparator_price_asc);
        store->items = itemsTMP;
        store = store->next_node;
    }

    return og_store;
}
Store_Type *generate_store(int item_len, Store_Type *next_node, char **item_names, char **store_names)
{
    int store_number = rand() % STORE_NAMES_LEN;
    Store_Type *store = (Store_Type *)malloc(sizeof(Store_Type));
    store->name = (char*)malloc(strlen(store_names[store_number])*sizeof(char)+1);
    memcpy(store->name, store_names[store_number],strlen(store_names[store_number])+1);
    store->items = generate_items(item_len, item_names);
    store->next_node = next_node;
    store->item_amount = item_len;
    store->total_price = -1;
    return store;
}
Item_Type **generate_items(size_t len, char **item_names)
{
    Item_Type **items = (Item_Type **)malloc(sizeof(Item_Type *) * (len));
    for (int i = 0; i < len; ++i)
    {
        items[i] = generate_item(item_names);
    }
    return items;
}
Item_Type *generate_item(char **item_names)
{

    int item_number_rand = rand() % ITEM_NAMES_LEN;

    Item_Type *item = (Item_Type *)malloc(sizeof(Item_Type));
    item->name = (char*)malloc(sizeof(char)*strlen(item_names[item_number_rand])+1);                   // Remember to free
    memcpy(item->name, item_names[item_number_rand], strlen(item_names[item_number_rand])+1); // Maybe use memccpy
    item->organic = rand() % 2;
    double number3 =(float)rand()/(float)(RAND_MAX) + rand() % (PRICE_RANGE_UPPER - PRICE_RANGE_LOWER) + PRICE_RANGE_LOWER;
    item->price = number3;
    item->unit = rand() % 5;
    item->unit_size = rand() % ((UNIT_RANGE_UPPER + 1) - UNIT_RANGE_LOWER) + UNIT_RANGE_LOWER; // Includes top range and lower range

    return item;
}

void free_item_test(Item_Type *item)
{
    //free(item->name);
    free(item);
}
void free_items(Item_Type **items, size_t len)
{
    for (int i = 0; i < len; ++i) {
        free_item_test(items[i]);
    }
    free(items);
}
void free_store_test(Store_Type *store)
{
    free_items(store->items, store->item_amount);
    free(store->name);
    free(store);
}
void free_all_stores_test(Store_Type *store)
{
    while (store != NULL)
    {
        Store_Type *next_store = store->next_node;
        free_store_test(store);
        store = next_store;
    }
}
void print_item(Item_Type *item)
{
    printf("NAME: %s\n", item->name);
    printf("PRICE: %.2lf\n", item->price);
    printf("ORGANIC: %d\n", item->organic);
    printf("UNIT_SIZE: %d\n", item->unit_size);
    printf("UNIT: %s\n", unit_type_to_str(item->unit));
}
void print_all_items(Item_Type **items, size_t len)
{
    for (int i = 0; i < len; ++i) {
        print_item(items[i]);
        printf("\n");
    }
}
void print_store_test(Store_Type *store)
{
    printf("STORE NAME: %s ----------------------------------------------------\n", store->name);
    print_all_items(store->items, store->item_amount);
}
void print_all_stores_test(Store_Type *store)
{
    while (store != NULL)
    {
        print_store_test(store);
        store = store->next_node;
    }
}
int comparator_price_asc(const void *p, const void *q)
{
    Item_Type* item1 = *(Item_Type**)p;
    Item_Type* item2 = *(Item_Type**)q;
    if (item1->price < item2->price)
        return -1;
    else if (item1->price > item2->price)
        return 1;
    else
        return 0;
}