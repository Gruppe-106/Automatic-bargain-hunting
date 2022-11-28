#include "../randomly_generated_testcases/random_testcases.h"
#include "../src/search/search.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

void how_it_works(void);

int main(void)
{
    how_it_works();
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