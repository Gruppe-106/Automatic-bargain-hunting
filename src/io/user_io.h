#ifndef AUTOMATIC_BARGAIN_HUNTING_USER_IO_H
#define AUTOMATIC_BARGAIN_HUNTING_USER_IO_H


typedef struct Input_Item {
    char* input;
    int quantity;
    struct Input_Item *next_input;
} Input_Item;


Input_Item* create_new_input_item(char* name,int quantity);
Input_Item *input_grocery_list();

void append_input_item_node(Input_Item* list, char* input, int quantity);
void read_item_string(char *string, Input_Item **grocery_list);


#endif //AUTOMATIC_BARGAIN_HUNTING_USER_IO_H
