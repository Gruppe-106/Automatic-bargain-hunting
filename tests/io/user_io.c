#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "../../src/io/user_io.h"
#include "../../src/util/user_io_utility.h"
#include "../../src/util/node_handler.h"


void test_input_grocery_list()
{
    char* no_input = "!find\n";
    FILE *input_file = fopen("input.txt", "w");
    fputs(no_input, input_file);
    fclose(input_file);

    input_file = freopen("input.txt", "r", stdin);

    Input_Item *grocery_list = input_grocery_list();
    fclose(input_file);

    remove("input.txt");
    free_grocery_list(grocery_list);

    assert(grocery_list == NULL);


    char *input = "mealk\nbananer\n!find\n";

    input_file = fopen("input.txt", "w");
    fputs(input, input_file);
    fclose(input_file);

    // open the input file for reading and redirect the standard input stream to it
    input_file = freopen("input.txt", "r", stdin);


    // call the input_grocery_list function
    grocery_list = input_grocery_list();
    fclose(input_file);

    // check the output
    assert(grocery_list != NULL);
    assert(grocery_list->next_input != NULL);
    assert(strcmp(grocery_list->input, "mealk") == 0);
    assert(strcmp(grocery_list->next_input->input, "bananer") == 0);

    remove("input.txt");
    free_grocery_list(grocery_list);
}


int main() {
    // Run unit tests
    test_input_grocery_list();

    // If all tests pass, return success
    return EXIT_SUCCESS;
}
