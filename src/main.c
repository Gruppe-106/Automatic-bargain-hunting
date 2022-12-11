#include "data_manager/data_loader.h"
#include "io/user_io.h"
#include "search/search.h"
#include "data_manager/sort_stores.h"
#include "data_manager/rank_stores.h"
#include "util/user_io_utility.h"
#include "util/node_handler.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    Store_Type *all_stores = load_all_data();
    sort_stores_items(&all_stores);
    Input_Item *items_to_find = input_grocery_list(false);

    size_t length;
    Store_Result_Type **results = search_stores(items_to_find, all_stores, &length);

    sort_results(&results, length);
    print_results(length, results);

    free_grocery_list(items_to_find);
    free_results(results, length);
    free_stores(all_stores);
    return 0;
}