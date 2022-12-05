#include "data_loader.h"

#define BILKA_PATH "data/bilka.json"
#define COOP_PATH "data/coop.json"
#define FOETEX_PATH "data/foetex.json"
#define REMA_PATH "data/rema-1000.json"

Store_Type* load_all_data() {
    Store_Type *all_stores = NULL;

    update_stores(json_parse_file(BILKA_PATH), &all_stores, "Bilka");
    update_stores(json_parse_file(COOP_PATH), &all_stores, "Coop");
    update_stores(json_parse_file(FOETEX_PATH), &all_stores, "Foetex");
    update_stores(json_parse_file(REMA_PATH), &all_stores, "Rema-1000");

    return all_stores;
}