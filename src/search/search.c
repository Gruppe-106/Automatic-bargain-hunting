#include "search.h"
#include <stdlib.h>
#include <string.h>

/* Prototypes */
int count_spaces(const char* string);
char** create_wordlist(const char* sent, size_t* length_output);
void free_wordlist(char** wordlist, size_t len);

/* Definitions */
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
     * For the size of all words, go ahead and make a wordlist of each product's name, and if any word matches any word
     * of the query wordlist, then a match is found and break out asap and proceed to the next product, when the
     * wordlist is freed.
     */
    for (int i = 0; i < size; ++i) {
        /* Make a wordlist of the name string. */
        size_t name_wordlist_len;
        char** name_wordlist = create_wordlist(items[i]->name, &name_wordlist_len);

        /* Find a match in the two wordlists. */
        for (int k = 0; k < name_wordlist_len; ++k) {
            int match_found = 0;
            for (int j = 0; j < query_wordlist_len; ++j) {
                if (strcmp(name_wordlist[k], query_wordlist[j]) == 0) {
                    matches_arr[matches] = items[i];
                    matches++;
                    match_found = 1;
                    break;
                }
            }
            if (match_found == 1) break;
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