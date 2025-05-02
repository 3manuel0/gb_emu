#include "cart.h"
#include "cpu.h"
#include <stdio.h>
#include <unistd.h>
int main(int arc, char ** argv){
    if(arc < 2) {
        printf("no argument given ./cart file-name\n");
        return -1;
    }
    CART cart = load_cart(argv[1]);
    //printing the first 400 instraction starting from 0x100
    sleep(10);
    printf("printing the first 400 instraction starting from 0x100\n");
    int i;
    u16 addr = 0x0100;
    while(i < 400){
        if(cart.roms_data[addr] == 0xc3){ 
           printf("0x%.2x op : %x afop: %x\n", addr,cart.roms_data[addr], (u16) (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8))); 
           addr = (cart.roms_data[addr + 1] | (cart.roms_data[addr + 2] << 8));
        }else {
           printf("0x%.2x : 0x%.2x\n", addr, cart.roms_data[addr]); 
            addr ++;
        }

        i++;
    }
    free(cart.roms_data);
    return 0;
}