#include "cpu.h"
#include <stdio.h>

void number_of_cycles(int t){
    printf("Cycle to wait for %d\n", t);
    return;
}

void run_inst(CPU_REGS * cpu_reg, u8 * roms_data){
    switch (roms_data[cpu_reg->PC]) {
        case 0x00:
            printf("0x%2x:the zero instruction 0x%.2x \n", cpu_reg->PC, roms_data[cpu_reg->PC]);
            cpu_reg->PC++;
            // add cycle time to emulate the gb cpu cycles
            number_of_cycles(4);
            break;
        case 0x01: 
            cpu_reg->BC = (roms_data[cpu_reg->PC + 1] | (roms_data[cpu_reg->PC + 2] << 8));
            printf("0x%.2x op : %.2x BC = %x\n", cpu_reg->PC, roms_data[cpu_reg->PC] , cpu_reg->BC);
            cpu_reg->PC += 3;
            number_of_cycles(12);
            break;
        case 0x02: 
            cpu_reg->BC = cpu_reg->AF;
            printf("0x%.2x op : %x new_BC = %x\n", cpu_reg->PC, roms_data[cpu_reg->PC], cpu_reg->BC); 
            cpu_reg->PC ++;
            number_of_cycles(8);
            break;
        case 0x03: 
            cpu_reg->BC++;
            printf("0x%.2x op : %x inc_BC = %x\n", cpu_reg->PC, roms_data[cpu_reg->PC], cpu_reg->BC); 
            cpu_reg->PC ++;
            number_of_cycles(8);
            break;            
        case 0xc3: 
            printf("0x%.2x op : %x afop: %x\n", cpu_reg->PC,roms_data[cpu_reg->PC], (u16) (roms_data[cpu_reg->PC + 1] | (roms_data[cpu_reg->PC + 2] << 8))); 
            cpu_reg->PC = (roms_data[cpu_reg->PC + 1] | (roms_data[cpu_reg->PC + 2] << 8));
            number_of_cycles(16);
            break;
        default: 
            printf("0x%.2x : 0x%.2x\n", cpu_reg->PC, roms_data[cpu_reg->PC]); 
            cpu_reg->PC++;
            break;
    }
}