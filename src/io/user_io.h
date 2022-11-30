#ifndef AUTOMATIC_BARGAIN_HUNTING_USER_IO_H
#define AUTOMATIC_BARGAIN_HUNTING_USER_IO_H


typedef struct Input_Item {
    char* input;
    struct Input_Item *next_input;
} Input_Item;


Input_Item* create_new_input_item(char* name);
void append_input_item_node(Input_Item** list, char* input);
void user_driver();

#endif //AUTOMATIC_BARGAIN_HUNTING_USER_IO_H
