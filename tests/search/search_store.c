#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "../../src/search/search.h"
#include "../../src/util/node_handler.h"


/*
typedef struct {
    char* store;
    Query_Result_Type** results;
    int results_len;
    int missing_items;
    double price_of_groceries;
} Store_Result_Type;½
*/

#define NUM_OF_STORES 10

void free_test_memory(Store_Result_Type **results, size_t results_len) {
    for (int i = 0; i < results_len; ++i) {
        free(results[i]);
    }
    free(results);
}

void free_test_input_item_list(Input_Item *query_items) {
    Input_Item *current_item = query_items;
    while (current_item != NULL) {
        Input_Item *next_item = current_item->next_input;
        free(current_item);
        current_item = next_item;
    }
}

void free_test_stores(Store_Type *all_stores) {
    Store_Type *current_store = all_stores;
    while (current_store != NULL) {
        Store_Type *next_store = current_store->next_node;
        for (int i = 0; i < current_store->item_amount; i++) {
            free(current_store->items[i]);
        }
        free(current_store->items);
        free(current_store);
        current_store = next_store;
    }
}

void generate_random_items(Store_Type *store) {
    srand(time(0));
    char *item_names[] = {"mealk", "ris", "toast"};
    int num_items = rand() % 3;
    store->item_amount =  num_items;
    store->items = (Item_Type**)malloc(sizeof(Item_Type*) * num_items);
    for (int i = 0; i < num_items; i++) {
        Item_Type *new_item = (Item_Type*)malloc(sizeof(Item_Type));
        new_item->name = item_names[rand() % num_items];
        new_item->unit = EACH;
        new_item->unit_size = 10.0;
        new_item->price = (rand() % 100) / 10.0;
        store->items[i] = new_item;
    }
}


void test_search_stores() {
    // Create a list of input items
    Input_Item *query_items = create_new_input_item("toast", 1);
    append_input_item_node(query_items, "mealk", 2);
    append_input_item_node(query_items, "ris", 3);

    // Create a list of stores
    Store_Type *all_stores = (Store_Type*)malloc(sizeof(Store_Type));
    all_stores->name = "foetex";
    generate_random_items(all_stores);
    all_stores->next_node = (Store_Type*)malloc(sizeof(Store_Type));
    all_stores->next_node->name = "bilka";
    generate_random_items(all_stores->next_node);
    all_stores->next_node->next_node = (Store_Type*)malloc(sizeof(Store_Type));
    all_stores->next_node->next_node->name = "lidl";
    generate_random_items(all_stores->next_node->next_node);
    all_stores->next_node->next_node->next_node = NULL;

    // Call the search_stores function
    size_t results_len;
    Store_Result_Type **results = search_stores(query_items, all_stores, &results_len);

    // Check the number of search results
    assert(results_len == 3);

    for (int i = 0; i < results_len; ++i) {
        assert(results[i]->price_of_groceries >= 0);
        assert(results[i]->missing_items >= 0);

    }

    assert(strcmp(results[0]->store,"foetex")== 0);
    assert(strcmp(results[1]->store,"bilka")== 0);
    assert(strcmp(results[2]->store,"lidl")== 0);

    free_test_memory(results,3);
    free_test_input_item_list(query_items);
    free_test_stores(all_stores);
}

int main(void){
    test_search_stores();

    return EXIT_SUCCESS;
}
