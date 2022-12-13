#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../../libs/parson/parson.h"
#include "../../src/data_manager/data_manager.h"
#include "../../src/util/unit_type_conversion.h"
#include "../../src/util/string_utility.h"

static char *rand_string(size_t size)
{
    char* str = (char*) malloc(sizeof(char) * (size + 1));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

JSON_Value* create_random_test_json(int amount) {
    JSON_Value *jsonValueArray = json_value_init_array();
    JSON_Array *jsonArray = json_value_get_array(jsonValueArray);

    for (int i = 0; i < amount; ++i) {
        JSON_Value *jsonValueObject = json_value_init_object();
        JSON_Object *jsonObject = json_value_get_object(jsonValueObject);

        json_object_dotset_string(jsonObject, "name", rand_string(10));
        json_object_dotset_string(jsonObject, "brand", rand_string(10));
        json_object_dotset_number(jsonObject, "price", rand() % 100);

        JSON_Value *ppuValue = json_value_init_object();
        JSON_Object *ppuObject = json_value_get_object(ppuValue);

        json_object_dotset_number(ppuObject, "price", rand() % 100);
        json_object_dotset_string(ppuObject, "unit", unit_type_to_str(rand() % 8));

        json_object_dotset_value(jsonObject, "price_pr_unit", ppuValue);

        json_object_dotset_number(jsonObject, "unit_size", rand() % 100);
        json_object_dotset_string(jsonObject, "unit_type", unit_type_to_str(rand() % 7));

        json_array_append_value(jsonArray, jsonValueObject);
    }

    return jsonValueArray;
}

_Bool compare_object_to_item(Item_Type* item, JSON_Object* jsonObject) {
    char* name = (char*) json_object_dotget_string(jsonObject, "name");
    if (str_contains_str(item->name, name, false) == -1) {
        printf("Expected: %s, got: %s\n", name, item->name);
        return EXIT_FAILURE;
    }

    double jsonPrice = json_object_dotget_number(jsonObject, "price");
    if (item->price != jsonPrice) {
        printf("Expected: %lf, got: %lf\n", jsonPrice, item->price);
        return EXIT_FAILURE;
    }

    double jsonUnitSize = json_object_dotget_number(jsonObject, "unit_size");
    if (item->unit_size != jsonUnitSize) {
        printf("Expected: %lf, got: %lf\n", jsonUnitSize, item->unit_size);
        return EXIT_FAILURE;
    }

    Unit_Type jsonUnitType = str_to_unit_type((char*) json_object_dotget_string(jsonObject, "unit_type"));
    if (item->unit != jsonUnitType) {
        printf("Expected: %u, got: %u\n", jsonUnitType, item->unit);
        return EXIT_FAILURE;
    }

    if(str_contains_str(name, "oeko", false) != -1 && item->organic != true) {
        printf("Expected: true, got: false\n");
        return EXIT_FAILURE;
    } else if(str_contains_str(name, "oeko", false) == 1 && item->organic == true) {
        printf("Expected: false, got: true\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(void) {
    int itemsAmount = 10;
    char* storeName = rand_string(10);
    srand(time(NULL));

    Store_Type *storeType = NULL;

    JSON_Value *jsonValue = create_random_test_json(itemsAmount);
    JSON_Value *jsonCheck = json_value_deep_copy(jsonValue);

    update_stores(jsonValue, &storeType, storeName);

    JSON_Array *jsonArray = json_value_get_array(jsonCheck);

    if (strcmp(storeType->name, storeName) != 0) return EXIT_FAILURE;
    Item_Type** items = storeType->items;
    for (int i = 0; i < itemsAmount; ++i) {
        JSON_Object *jsonObject = json_array_get_object(jsonArray, i);
        Item_Type *item = items[i];
        _Bool success = compare_object_to_item(item, jsonObject);
        if (success == EXIT_FAILURE) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}