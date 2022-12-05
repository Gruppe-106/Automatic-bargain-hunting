#include "data_manager/data_loader.h"
#include "io/user_io.h"
#include "search/search.h"
#include "data_manager/sort_stores.h"
#include "data_manager/rank_stores.h"
#include "util/user_io_utility.h"
#include "util/node_handler.h"

int main(void) {
    Store_Type *all_stores = load_all_data();
    all_stores = sort_store_items(all_stores);
    /* Input_Item *grocery_list = user_driver(); */

    size_t len;
    Item_Type **items_found = find_items("fedt oeko minimaelk", all_stores->items, all_stores->item_amount, &len);

    print_items(items_found, len);
    free_query(items_found);

    free_stores(all_stores);
    /*
    print_grocery_list(grocery_list);
    free_grocery_list(grocery_list);
    */

    return 0;
}