#include "../parson/parson.h"
#include "../parson/parson.c"


void persistence_example(void);

int main(void){
    persistence_example();
    return 0;
}

void persistence_example(void) {
    JSON_Value *bargins = json_parse_file("./data/salling.json");
    char *nenene = json_serialize_to_string_pretty(bargins);
    puts(nenene);

}