#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../src/data_manager/data_manager.h"
#include "../../src/search/search.h"

void test_find_items()
{

    const char *query = "mealk";

    Item_Type item1 = {"aeble", 1, 1, EACH, 0};
    Item_Type item2 = {"mealk", 2, 1, EACH, 0};
    Item_Type item3 = {"vand", 3, 1, EACH, 0};
    Item_Type item4 = {"kage", 4, 1, EACH, 0};
    Item_Type item5 = {"fisk", 5, 1, LITER, 0};
    Item_Type item6 = {"ris", 6, 1, LITER, 0};
    Item_Type item7 = {"kaffe", 7, 1, LITER, 0};
    Item_Type item8 = {"madpandekager", 8, 1, LITER, 0};
    Item_Type item9 = {"mealk", 9, 1, LITER, 0};
    Item_Type item10 = {"spand", 10, 1, LITER, 0};

    Item_Type *items[] = {&item1, &item2, &item3, &item4, &item5, &item6, &item7, &item8, &item9, &item10};

    size_t size = 10;

    size_t result_size;
    Item_Type **result = find_items(query, items, size, &result_size);

    assert(result_size == 2);

    for (int i = 0; i < result_size; ++i)
    {
        assert(strcmp(result[i]->name, query) == 0);
    }
}

int main(void)
{
    test_find_items();
    return EXIT_SUCCESS;
}