#include "../parson/parson.h"
#include "../parson/parson.c"


void persistence_example(void);

int main(void){
    persistence_example();
    return 0;
}


void persistence_example(void) {
    JSON_Value  *salling = json_parse_file("./data/salling.json");
    JSON_Array  *clearences;
    JSON_Object *;

}