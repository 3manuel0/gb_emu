#include "cart.h"


int main(int arc, char ** argv){
    unsigned char ch;
    size_t sz;
    char newCode[3];
    if(arc < 2) {
        printf("no argument given ./cart file-name\n");
        return -1;
    }
    FILE * f = fopen(argv[1], "rb");
    CART cart = {0};
    if(f == NULL){
        printf("can't open file");
        return 1;
    }
    fseek(f, 0L, SEEK_END);
    sz = ftell(f);
    rewind(f);
    cart.roms_data = malloc(sz);
    printf("sz : %ld\n", sz);
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
    
    // printing the header

    printf("Title: %s\n", cart.Title);
    printf("cgb: %x\n", cart.cgb);
    printf("manf: %s\t %02x\n", getmanif[cart.manif], cart.manif);
    printf("New Code: %c%c\n", newCode[0], newCode[1]);
    printf("type: %d\n", cart.type);
    printf("size: %dkib\t%d\n", 32 * (1 << cart.size), cart.size);
    u8 checksum = 0;
    for (u16 address = (u16)0x0134; address <= (u16)0x014C; address++) {
        checksum = checksum - cart.roms_data[address] - 1;
    }
    printf("verfy checksum : %x\n", cart.roms_data[0x14D]);
    printf("Checksum : %x\n", checksum);
    // printf("op : %x %x\n", cart.roms_data[0x28b], cart.roms_data[(u16) (cart.roms_data[0x0102] | (cart.roms_data[0x0103] << 8)) + 1]);
    int i;
    u16 addr = (u16)0x0100;
    while(i < 400){
        if(cart.roms_data[addr] == 0xc3){ 
           printf("0x%.2x op : %x afop: %x\n", addr,cart.roms_data[addr], (u16) (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8))); 
           addr = (u16) (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8));
        }else {
           printf("0x%.2x : 0x%.2x\n", addr, cart.roms_data[addr]); 
            addr ++;
        }

        i++;
    }
    return 0;
}