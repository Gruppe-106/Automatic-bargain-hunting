#include "search.h"
#include <stdlib.h>
#include <string.h>
#include "../io/user_io.h"
#include "../util/user_io_utility.h"
#include <stdio.h>

/* Prototypes */
int count_spaces(const char* string);
char** create_wordlist(const char* sent, size_t* length_output);
void free_wordlist(char** wordlist, size_t len);

/* Definitions */
int get_store_len(Store_Type *all_stores);

Store_Result_Type *allocate_and_assign_results(Input_Item *query_items, const Store_Type *store);

void allocate_and_assign_result(Store_Type *store, Store_Result_Type *results, int i, const Input_Item *current_query);

/**
 * @brief Simply counts spaces
 * @param string the string in which spaces need to be counted
 * @return Returns the amount of spaces in 'string'
 */
int count_spaces(const char* string)
{
    int i = 0;
    int space_count = 0;
    char c = string[i];
    while (c != '\0')
    {
        if (c == ' ') space_count++;
        c = string[++i];
    }
    return space_count;
}

/**
 * @brief Frees the query, without freeing the items themselves, as they will be freed by another function
 * @param query_result the query result to be freed
 */
void free_query(Item_Type** query_result)
{
    free(query_result);
}

/**
 * @brief Creates a list of words from a sentence. This wordlist is separated by spaces
 * @param sent the sentence to be split
 * @param length_output the length of the array of words
 * @return Returns an array of words that are contained within 'sent'
 */
char** create_wordlist(const char* sent, size_t* length_output)
{
    /* Create a copy of sent */
    int sent_len = (int) strlen(sent);
    char tmp[sent_len + 1];
    strcpy(tmp, sent);

    /* Tokenize the copy of sent. This will be added to an array of words 'query_wordlist' */
    char* query_token = strtok(tmp, " ");
    int query_words = count_spaces(sent) + 1;
    char** query_wordlist = (char**) malloc(query_words * sizeof(char*));
    int k = 0;
    /* As long as query_token isn't NULL we know it isn't done, so allocate each word and append to the list */
    while (query_token != NULL)
    {
        int word_len = (int)strlen(query_token);
        query_wordlist[k] = (char*) malloc((word_len + 1) * sizeof(char));
        strcpy(query_wordlist[k], query_token);
        query_token = strtok(NULL, " ");
        ++k;
    }

    /* Assign return values and return the wordlist */
    *length_output = k;
    return query_wordlist;
}

/**
 * @brief Frees a wordlist by simply freeing the name then the list itself
 * @param wordlist the wordlist to be freed
 * @param len the length of the wordlist to be freed
 */
void free_wordlist(char** wordlist, size_t len)
{
    /* Simply free the words and then the array */
    for (int i = 0; i < len; ++i) free(wordlist[i]);
    free(wordlist);
}

/**
 * @brief Finds items in an array of items by the query. Any item containing any word in query will be returned.
 * @param query the words to search for
 * @param items the list of items to search in
 * @param size the size of this list of items
 * @param size_output a pointer to the variable that should hold the size of the given array of results
 * @return Returns an array of matching products.
 */
Item_Type** find_items(const char* query, Item_Type** items, size_t size, size_t* size_output)
{
    /* Creates an array big enough to hold all possible matches. (Only exists for function lifetime) */
    Item_Type* matches_arr[size];
    /* To keep track of the amount of matches in matches_arr. */
    size_t matches = 0;

    /* Make a query_wordlist of the query. Separates each word by ' ' and creates an array of words. */
    size_t query_wordlist_len;
    char** query_wordlist = create_wordlist(query, &query_wordlist_len);

    /*
     * For the size of all words, go ahead and make a wordlist of each product's name, and all words match
     * then a match is found and proceed to the next product, when the wordlist is freed
     */
    for (int i = 0; i < size; ++i) {
        /* Make a wordlist of the name string. */
        size_t name_wordlist_len;
        char** name_wordlist = create_wordlist(items[i]->name, &name_wordlist_len);

        /* Find a match in the two wordlists. */
        int match_found = 0;
        for (int k = 0; k < query_wordlist_len; ++k) {
            match_found = 0;
            for (int j = 0; j < name_wordlist_len; ++j) {
                if (strcmp(name_wordlist[j], query_wordlist[k]) == 0) {
                    match_found = 1;
                    break;
                }
            }
            if (match_found == 1) continue;
            else break;
        }
        if (match_found == 1)
        {
            matches_arr[matches] = items[i];
            matches++;
        }

        /* Remember to free */
        free_wordlist(name_wordlist, name_wordlist_len);
    }

    /* Copy the matches from the matches_arr to an appropriately sized array of matches to return */
    Item_Type** items_to_return = (Item_Type**) malloc(matches * sizeof(Item_Type*));
    for (int i = 0; i < matches; ++i) {
        items_to_return[i] = matches_arr[i];
    }

    /* Free the wordlist of the query */
    free_wordlist(query_wordlist, query_wordlist_len);

    /* Assign the return values and return the list with matches. */
    *size_output = matches;
    return items_to_return;
}

/**
 * @brief Creates a query for each of the Input_Items. All data is held in Store_Result_Type.
 * @param query_items Items to search for.
 * @param store The store to search in.
 * @return Returns all matching items from this store.
 */
Store_Result_Type *search_store(Input_Item *query_items, Store_Type* store)
{
    Store_Result_Type *results = allocate_and_assign_results(query_items, store);

    int i = 0;
    Input_Item *current = query_items;
    while (current != NULL)
    {
        allocate_and_assign_result(store, results, i, current);
        ++i;
        current = current->next_input;
    }

    return results;
}

/**
 * @brief Allocates and assigns results[i] to the proper name, and finds the items.
 * @param store The store in which to search.
 * @param results The array in which to store the query result.
 * @param i The index in the array the query should be stored.
 * @param current_query The current query string.
 */
void allocate_and_assign_result(Store_Type *store, Store_Result_Type *results, int i, const Input_Item *current_query) {
    results->results[i] = (Query_Result_Type*) malloc(sizeof(Query_Result_Type));
    size_t query_name_len = strlen(current_query->input);
    results->results[i]->query = (char*) malloc(sizeof(char) * (query_name_len + 1));
    memcpy(results->results[i]->query, current_query->input, query_name_len + 1);
    results->results[i]->items_result = find_items(
            results->results[i]->query,
            store->items, store->item_amount,
            &results->results[i]->items_len
    );
}

/**
 * @brief Allocates a Store_Result_Type struct, such that it can contain the name of it, and the query results, as well as the length of these.
 * @param query_items
 * @param store
 * @return
 */
Store_Result_Type *allocate_and_assign_results(Input_Item *query_items, const Store_Type *store) {
    Store_Result_Type *result_query = (Store_Result_Type*) malloc(sizeof(Store_Result_Type));
    size_t name_len = strlen(store->name);
    result_query->store = (char*) malloc(sizeof(char) * (name_len + 1));
    memcpy(result_query->store, store->name, name_len + 1);

    int queries = grocery_list_length(query_items);
    result_query->results_len = queries;
    result_query->results = (Query_Result_Type**) malloc(queries * sizeof(Query_Result_Type*));
    return result_query;
}

/**
 * @brief Creates a query for each of the Input_Items for every store. All data is held in an array of Store_Result_Type pointers.
 * @param query_items Items to searc for.
 * @param all_stores The store to search in.
 * @param results_len_output The length of the output array containing query data.
 * @return Returns an array containing query data for each store.
 */
Store_Result_Type **search_stores(Input_Item *query_items, Store_Type* all_stores, size_t *results_len_output)
{
    int stores_len = get_store_len(all_stores);
    Store_Result_Type **return_store_queries = (Store_Result_Type**) malloc(sizeof(Store_Result_Type*) * stores_len);

    Store_Type *current_store = all_stores;
    int i = 0;
    while (current_store != NULL)
    {
        return_store_queries[i] = search_store(query_items, current_store);
        current_store = current_store->next_node;
        i++;
    }

    *results_len_output = i;
    return return_store_queries;
}

/**
 * @brief Gets the length of the node.
 * @param all_stores The first store node in the linked list.
 * @return Returns the length of the linked list.
 */
int get_store_len(Store_Type *all_stores) {
    int stores_len = 0;
    Store_Type *current_store = all_stores;
    while (current_store != NULL)
    {
        current_store = current_store->next_node;
        stores_len++;
    }
    return stores_len;
}

/**
 * @brief Prints all results from queries.
 * @param store_res The queries, created by search_stores.
 * @param store_size The size of the array that holds all query data.
 */
void print_results(Store_Result_Type** store_res, size_t store_size)
{
    for (int l = 0; l < store_size; ++l) {
        printf("STORE NAME: %s\n", store_res[l]->store);
        for (int i = 0; i < store_res[l]->results_len; ++i) {
            printf("QUERY: %s\n", store_res[l]->results[i]->query);
            for (int j = 0; j < store_res[l]->results[i]->items_len; ++j) {
                printf("%d: \'%s\' = %lf\n", j + 1, store_res[l]->results[i]->items_result[j]->name, store_res[l]->results[i]->items_result[j]->price);
            }
        }
        printf("\n\n");
    }
}

/**
 * @brief Frees all the query data contained in the array.
 * @param store_res Array of all query data.
 * @param store_size The size of the array containing query data.
 */
void free_results(Store_Result_Type** store_res, size_t store_size)
{
    for (int i = 0; i < store_size; ++i) {
        for (int j = 0; j < store_res[i]->results_len; ++j) {
            free(store_res[i]->results[j]->query);
            free(store_res[i]->results[j]->items_result);
            free(store_res[i]->results[j]);
        }
        free(store_res[i]->store);
    }
    free(store_res);
}