#include "../randomly_generated_testcases/random_testcases.h"
#include "../src/search/search.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main(void)
{
    Store_Type* store = generate_stores_sorted(5, 5);
    rank_all_stores(store);
    print_all_stores_test(store);
    free_all_stores_test(store);
}

void tester1(void)
{
    Store_Type* store = generate_stores_sorted(1, 300);
    Store_Type* og_store = store;

    int i = 0;
    while (store)
    {
        int size_list;
        Item_Type** results = find_items_in_items_by_str("oeko", store->items, &size_list);
        printf("QUERY: %d ---------------------------------------------\n", i++);
        print_all_items(results, size_list);
        free(results);
        store = store->next_node;
    }
    free_all_stores_test(store);
}