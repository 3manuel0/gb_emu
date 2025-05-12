#define CPU_H

#ifdef CPU_H
    #include "def.h"

    typedef struct {
        u16 AF;//Accumulator & Flags
        u16 BC;
        u16 DE;
        u16 HL;
        u16 SP;//Stack Pointer
        u16 PC;//Program Counter/Pointer
    }CPU_REGS;


    void run_inst(CPU_REGS * cpu_reg, u8 * roms_data);

#endif