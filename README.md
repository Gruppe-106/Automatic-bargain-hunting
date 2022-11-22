# Automatic Bargain Hunting
## Structure
### ../src
```
data_manager/
    api_manager.c       //Potentially, use static data for now
    json_parser.c       //String to json object helper using parson library
    data_manager.c      //Convert json object to our own data structure and categoriziation
search/
   search.c             //Search by store, item and/or categorice etc.
   categorize_input.c   //Helper for function for user input to search
ui/
    UserIO.c            //User input/output handler

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
    int unit_size;
    Unit_Type unit;
    _Bool organic;
}
```
### Data storage
```
Store -> Category -> ? Items[]
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
