#ifndef AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
#define AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H

typedef enum {
    GRAM,
    KILOGRAM,
    LITER,
    MILLILITER,
} Unit_Type;

typedef struct {
    char* name;
    double price;
    int unit_size;
    Unit_Type unit;
    _Bool organic;
} Item_Type;

// Prototypes

#endif //AUTOMATIC_BARGAIN_HUNTING_DATA_MANAGER_H
