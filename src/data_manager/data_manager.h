#ifndef AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#define AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H

typedef enum {
    GRAM,
    KILOGRAM,
    LITER,
    MILLILITER,
    each,
} Unit_Type;

/* This is an obtuse type, you cannot ascces it's inner members, but you can use functions and such */
typedef struct item item_type;


// Prototypes

Item_Type* create_item(char* name, double price, int unit_size, Unit_Type unit, _Bool organic);
#endif //AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
