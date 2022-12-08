#include "data_manager/data_loader.h"
#include "io/user_io.h"
#include "search/search.h"
#include "data_manager/sort_stores.h"
#include "data_manager/rank_stores.h"
#include "util/user_io_utility.h"
#include "util/node_handler.h"
#include <stdio.h>

int main(void) {
    Store_Type *all_stores = load_all_data();
    sort_stores_items(&all_stores);
    Input_Item *items_to_find = input_grocery_list();

    size_t length;
    Store_Result_Type **results = search_stores(items_to_find, all_stores, &length);


    print_results(results, length);
    sort_results(&results, length);
    for (int i = 0; i < length; ++i) {
        printf("STORE: %s\n", results[i]->store);
        printf("Total Grocery List Price: %lf\n", results[i]->price_of_groceries);
        printf("Total Missing Items: %d\n\n", results[i]->missing_items);
    }

    free_results(results, length);
    free_stores(all_stores);
    return 0;
}