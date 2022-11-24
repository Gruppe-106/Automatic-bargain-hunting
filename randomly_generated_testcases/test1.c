#include "../randomly_generated_testcases/random_testcases.h"
#include "../src/search/search.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main(void)
{
    Store_Type* store = generate_stores_sorted(1, 300);
    Store_Type* og_store = store;

    int i = 0;
    while (store)
    {
        Item_Type** results = find_items_in_items_by_str("oeko", store->items);
        printf("QUERY: %d ---------------------------------------------\n", i++);
        print_all_items(results);
        free(results);
        store = store->next_node;
    }


    free_all_stores_test(store);
}