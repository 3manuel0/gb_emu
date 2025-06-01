#include "cart.h"
#include "cpu.h"
#include "ppu.h"




int main(int arc, char ** argv){
    if(arc < 2) {
        printf("no argument given ./gb file-name\n");
        return -1;
    }
    CART cart = load_cart(argv[1]);

    if(cart.roms_data == NULL) {
        return -1;
    }
    
    CPU_REGS cpu = {0};
    
    u8 memory[0x10000];
    memcpy(memory , cart.roms_data, sizeof(memory));
    free(cart.roms_data);

    //printing the first 100 instraction starting from 0x100
    printf("printing the first 100 instraction starting from 0x100\n");
    cpu.PC = 0x0100;
    int i = 0;
    while(i < 100){
        run_inst(&cpu, memory);
        sleep(1);
        i++;
    }

    cpu.PC = 0x8000;
    // InitWindow(1200, 720, "test");
    // // nintendo logo 0x0104 to 0x0133
    // while(!WindowShouldClose()){
    //     BeginDrawing();
    //     cpu.PC = 0x9800;
    //     ClearBackground(WHITE);
    //     u32 j = 0;
    //     for(u32 i = cpu.PC; i < 0x9BFF; i+=2){
    //         if(j <= 32){
    //             // printf("0x%.2x, 0x%.2x, %d\n", i, i + 1, j);
    //             draw_tile(cart.roms_data[i], cart.roms_data[i + 1], &j);
    //         }
    //     }

    //     EndDrawing();
    // }
    return 0;
}