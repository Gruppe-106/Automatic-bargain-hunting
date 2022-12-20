# Automatic Bargain Hunting
This repository is part of a project for the Computer Science Group 106 at Aalborg University.
The code produced for the project can be found in the data, src & test folder, structure of src can be seen below. Other directories are not part of the final product.
## Structure
### ../src
```
data_manager/
    data_loader.c/.h        // Loads JSON and parses them to data_manager.c
    data_manager.c/.h       // Convert json object to our own data structure and categoriziation
    sort_stores.c/.h        // Sorts stores lists of items by price for faster searching
search/
   search.c                 // Search by store, item and/or categorice etc.
IO/
    UserIO.c                // User input/output handler
util/
    node_handler.c          // Helper functions for a linked list for the store type in data_manager.h
    string_utility.c        // String helper functions 
    unit_type_conversion.c  // Helper functions for converting and homogonising unit type within Item_Type
main.c                      // Injection point
```
## Data structure
```
typedef enum {
    gram,
    kilogram,
    liter,
    mililiter,
    ...
} Unit_Type

typedef struct item {
    char* name;
    double price;
    double unit_size;
    Unit_Type unit;
    _Bool organic;
} Item_Type;
```
### Data storage
```
typedef struct store {
    char* name;
    Item_Type** items;
    size_t item_amount;
    double total_price;
    struct store* next_node;
} Store_Type;
```
