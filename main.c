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
    CPU_REGS cpu = {0};
    //printing the first 400 instraction starting from 0x100
    // sleep(10);
    printf("printing the first 400 instraction starting from 0x100\n");
    int i;
    cpu.PC = 0x0100;
    while(i < 400){
        run_inst(&cpu, cart.roms_data);
        i++;
    }
    free(cart.roms_data);
    printf("CPU_REGSs: %zu", sizeof(CART));
    return 0;
}