#define CART_H
#ifdef CART_H
    #include "def.h"
    typedef  struct{
        u8* roms_data;
        u8 Title[(0x143 - 0x134) + 1];
        u8 cgb;
        u8 manif;
        u8 type;
        u8 size;
    } CART;

    CART load_cart(char * cartName);

#endif