# Automatic Bargain Hunting
## Structure
### ../src
```
data_manager/
    rank_stores.c       //Used to ranke stores depending on prices -Andreas
    data_manager.c      //Convert json object to our own data structure and categoriziation -Mikkel
    sort_stores.c       //Sorts stores lists of items by price for faster searching - Christian
search/
   search.c             //Search by store, item and/or categorice etc. - Mads
ui/
    UserIO.c            //User input/output handler - Zeki || Simon
util/
    node_handler.c
    store_utility.c
    string_utility.c
    unit_type_conversion.c
main.c                  //Injection point, should not contain general algorithms
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

struct item {
    char* name;
    double price;
    double unit_size;
    Unit_Type unit;
    _Bool organic;
}
```
### Data storage
```
Main data storage
All stores =
    struct store {
        char* name;
        Item_Type** items;
        size_t item_amount;
        double total_price;
        struct store* next_node;
    }
```
## Examples
cmake is stupid right now and wont build the folder with data. Therefore GCC is needed
First check if already installed
```
gcc -v
```
### Installing GCC
Goto https://www.mingw-w64.org/downloads/ and install the latest version
### Building
```
gcc -g -w -Wall examples/example_{num}.c -o example_{num} -lm
```
### Running
In root open CMD and run
```
example_{num}.exe "./data/salling.json"
```
### Notes
```
As c uses acii character we need a solution for æ ø å.
```