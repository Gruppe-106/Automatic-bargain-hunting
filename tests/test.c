#include "../parson/parson.h"
#include "../parson/parson.c"
#include <stdio.h>

void persistence_example(void);

int main(void)
{
    persistence_example();
    return 0;
}

void persistence_example(void)
{
    JSON_Value *salling = json_parse_file("./data/salling.json");
    JSON_Array *clearences;
    JSON_Object *object;
    int clearences_size;

    if (json_value_get_type(salling) != JSONArray){
        return;
    }

    clearences      = json_value_get_array(salling);
    clearences_size = json_array_get_count(clearences);

    printf("%d",clearences_size);

    // for (int i = 0; i < clearences_size; i++){
        
    // }


    json_value_free(salling);


}

