#include "../randomly_generated_testcases/random_testcases.h"
#include "../randomly_generated_testcases/random_testcases.c"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

int main(void)
{
    Store_Type* store = generate_stores_unsorted(5, 5);
    print_all_stores_test(store);
    free_all_stores_test(store);

}