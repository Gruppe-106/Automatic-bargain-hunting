#include "../randomly_generated_testcases/random_testcases.h"
#include "../src/search/search.h"
#include <stdio.h>
#include "../src/data_manager/sort_stores.h"
#include "../src/util/node_handler.h"

void parse_search();

int main(void)
{
parse_search();
}

void parse_search()
{
    /* Create a store from JSON file and sort the store */
    JSON_Value* json = json_parse_file("data/rema-1000.json");
    Store_Type* store = NULL;
    update_stores(json, &store, "REMA");
    store = sort_store_items(store);

    /* Make a query and return the items that match a word in the query. This should be freed with 'free_query'. */
    size_t len_output = 0;
    Item_Type** items_match = find_items("oeko julemedister", store->items, store->item_amount, &len_output);



    /* Print items that match */
    print_all_items(items_match, len_output);

    /* Free the query */
    free_query(items_match);

    /* Freeing the store once again */
    free_stores(store);
}