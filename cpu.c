#include "cpu.h"
#include <stdio.h>

// add cycle time to emulate the gb cpu cycles
void number_of_cycles(int t){
    printf("Cycle to wait for %d\n", t);
    return;
}

void run_inst(CPU_REGS * cpu_reg, u8 * memory){
    switch (memory[cpu_reg->PC]) {
        case 0x00:
            // NOP
            printf("0x%2x:the zero instruction 0x%.2x \n", cpu_reg->PC, memory[cpu_reg->PC]);
            cpu_reg->PC++;
            number_of_cycles(4);
            break;
        case 0x01: 
            // LD BC, n16
            cpu_reg->BC = (memory[cpu_reg->PC + 1] | (memory[cpu_reg->PC + 2] << 8));
            printf("0x%.2x op : %.2x BC = %x\n", cpu_reg->PC, memory[cpu_reg->PC] , cpu_reg->BC);
            cpu_reg->PC += 3;
            number_of_cycles(12);
            break;
        case 0x02:
            // LD [BC], A 
            memory[cpu_reg->BC] = (cpu_reg->AF >> 8) & 0xFF;
            printf("0x%.2x op : %x BC = %x\n", cpu_reg->PC, memory[cpu_reg->PC], cpu_reg->BC); 
            cpu_reg->PC ++;
            number_of_cycles(8);
            break;
        case 0x03:
            // INC BC  
            cpu_reg->BC++;
            printf("0x%.2x op : %x BC = %x\n", cpu_reg->PC, memory[cpu_reg->PC], cpu_reg->BC); 
            cpu_reg->PC ++;
            number_of_cycles(8);
            break;            
        case 0xc3: 
            // JP a16
            printf("0x%.2x op : %x afop: %x\n", cpu_reg->PC,memory[cpu_reg->PC], (u16) (memory[cpu_reg->PC + 1] | (memory[cpu_reg->PC + 2] << 8))); 
            cpu_reg->PC = (memory[cpu_reg->PC + 1] | (memory[cpu_reg->PC + 2] << 8));
            number_of_cycles(16);
            break;
        case 0xfe:{ 
            u8 cmp = ((cpu_reg->AF >> 8) & 0xff) - memory[cpu_reg->PC + 1];
            printf("0x%.2x op : %x afop: %x %d diffrance\n", cpu_reg->PC,memory[cpu_reg->PC],memory[cpu_reg->PC + 1], cmp); 
            number_of_cycles(8);
            cpu_reg->PC += 2;
            break;
        }
        default: 
            printf("0x%.2x : 0x%.2x\n", cpu_reg->PC, memory[cpu_reg->PC]); 
            cpu_reg->PC++;
            break;
    }
}