#include "../randomly_generated_testcases/random_testcases.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main(void)
{
    Store_Type* store = generate_stores_unsorted(20, 20);
    print_all_stores_test(store);
    free_all_stores_test(store);
}