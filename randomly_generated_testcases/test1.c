#include "../randomly_generated_testcases/random_testcases.h"
#include "../src/search/search.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "../src/data_manager/sort_stores.h"
#include "../src/util/node_handler.h"
#include "../libs/parson/parson.h"
#include "../src/data_manager/data_manager.h"

void how_it_works(void);
void json_how_it_works(void);

int main(void)
{
    json_how_it_works();
}

void json_how_it_works(void)
{
    JSON_Value* json = json_parse_file("C:\\Users\\madsh\\CLionProjects\\Automatic-bargain-hunting\\data\\rema-1000.json");
    Store_Type* store = NULL;
    update_stores(json, &store, REMA);
    store = sort_store_items(store);

    int q_res_len;
    Item_Type** q_res = find_items_in_items_by_str("ris", store->items, store->item_amount, &q_res_len);
    print_all_items(q_res, q_res_len);

    free_stores(store);
}

void how_it_works(void)
{
    // Allocate an amount of stores and it's items
    int store_amount = 5,
        list_amount = 5;
    Store_Type* store = generate_stores_sorted(store_amount, list_amount);


    print_all_stores_test(store);

    // Free the stores and lists and items
    free_all_stores_test(store);
}