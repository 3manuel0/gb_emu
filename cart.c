#include "cart.h"

CART load_cart(char * cartName){
    unsigned char ch;
    size_t sz;
    char newCode[3] = "nn";
    FILE * f = fopen(cartName, "rb");
    CART cart = {0};
    if(f == NULL){
        printf("can't open file");
        exit(-1);
        return cart;
    }
    fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);
    cart.roms_data = malloc(sz);
    int str = 0;
    for (size_t i = 0; i < sz; i++) {
        ch = fgetc(f);
        if(i >= 0x134 && i < 0x143 ){
            cart.Title[str] = ch;
            // printf("Title : %c\n", ch);
            str++;
        }
        if(i == 0x143){
            cart.cgb = ch;
        }
        if(i == 0x144){
            newCode[0] = ch;
        }
        if (i == 0x145) {
            newCode[0] = ch;
        }
        if(i == 0x147){
            cart.type = ch;
        }
        if(i == 0x148){
            cart.size = ch;
        }
        if(i == 0x14B){
            cart.manif = ch;
        }
        // if(i < 0x14F)
        //     printf("%d ", ch);

        cart.roms_data[i] = ch;
    }
    
    u8 checksum = 0;
    for (u16 address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - cart.roms_data[address] - 1;
    }

    // printing the header
    printf("-------header----------------\n"); 
    printf("file size : %ld\n", sz);
    printf("Title: %s\n", cart.Title);
    printf("cgb: %x\n", cart.cgb);
    printf("manufacturer: %s\t %02x\n", getmanif[cart.manif], cart.manif);
    printf("New Code: %c%c\n", newCode[0], newCode[1]);
    printf("cart_type: %d\n", cart.type);
    printf("rom_size: %dkib\t%d\n", 32 * (1 << cart.size), cart.size);
    printf("checksum_value : %x\n", cart.roms_data[0x14D]);
    printf("Checksum_calc : %x %s\n", checksum,checksum == cart.roms_data[0x14D] ? "good" : "bad");
    // printf("op : %x %x\n", cart.roms_data[0x28b], cart.roms_data[(u16) (cart.roms_data[0x0102] | (cart.roms_data[0x0103] << 8)) + 1]);
    printf("------------------------------\n"); 
    return cart;
}