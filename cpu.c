#include "cpu.h"

void run_inst(CPU_REGS * cpu_reg, u8 * roms_data){
    switch (roms_data[cpu_reg->PC]) {
        case 0x00:
            printf("0x%2x:the zero instruction 0x%2x \n", cpu_reg->PC, roms_data[cpu_reg->PC]);
            cpu_reg->PC++;
            // add cycle time to emulate the gb cpu cycles
            // cycle_timer(4);
            break;
        case 0xc3: 
            printf("0x%.2x op : %x afop: %x\n", cpu_reg->PC,roms_data[cpu_reg->PC], (u16) (roms_data[cpu_reg->PC + 1] | (roms_data[cpu_reg->PC + 2] << 8))); 
            cpu_reg->PC = (roms_data[cpu_reg->PC + 1] | (roms_data[cpu_reg->PC + 2] << 8));
            break;
        default: 
            printf("0x%.2x : 0x%.2x\n", cpu_reg->PC, roms_data[cpu_reg->PC]); 
            cpu_reg->PC++;
            break;
    }
}