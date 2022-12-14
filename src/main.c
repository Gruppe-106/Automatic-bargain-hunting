#include "data_manager/data_loader.h"
#include "io/user_io.h"
#include "search/search.h"
#include "data_manager/sort_stores.h"
#include "util/node_handler.h"
#include <stdio.h>

int main(void) {
    Store_Type *all_stores = load_all_data();
    sort_stores_items(&all_stores);
    puts("You can use !find to look for items, and !quit to quit the program");
    Input_Item *items_to_find = input_grocery_list();

    size_t length;
    Store_Result_Type **results = search_stores(items_to_find, all_stores, &length);

    sort_results(&results, length);
    print_results(length, results);

    free_grocery_list(items_to_find);
    free_results(results, length);
    free_stores(all_stores);
    return 0;
}