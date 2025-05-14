#include "cart.h"
#include "cpu.h"
#include "ppu.h"
#include <stdio.h>
#include <unistd.h>
#include <raylib.h>

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
    // while(i < 400){
    //     run_inst(&cpu, cart.roms_data);
    //     i++;
    // }
    printf("CPU_REGSs: %zu\n", sizeof(CART));
    cpu.PC = 0x8000;
    InitWindow(1200, 720, "test");
    // nintendo logo 0x0104 to 0x0133
    while(!WindowShouldClose()){
        BeginDrawing();
        cpu.PC = 0x9800;
        ClearBackground(WHITE);
        u32 j = 0;
        for(u32 i = cpu.PC; i < 0x9BFF; i+=2){
            // if(j <= 32 * 4){
                // printf("0x%.2x, 0x%.2x, %d\n", i, i + 1, j);
                draw_tile(cart.roms_data[i], cart.roms_data[i + 1], &j);
            // }
        }

        EndDrawing();
    }
    free(cart.roms_data);
    return 0;
}