#include <bits/stdc++.h>
#include "component/CPU.h"

int main() {

    CPU::BUS* bus = new CPU::BUS(0x0000, 0xffff, false);

    // loads a program inside the virtual RAM
    /*
    bus->MEMORY = {
        // LDA #$3
        {0x0000, 0xA9},
        {0x0001, 0x03},
        // LDA #$FF
        {0x0002, 0x69},
        {0x0003, 0xFF}
    };
    */

    std::string prog = "A9 C0 AA E8 69 C4 00";
    bus->loadProgram(prog);

    printf("Program Size %i bits | %i Chuncks", bus->memSize(), bus->memSize() / 8);

    CPU::Core6502 cpu;
    cpu.Connect( bus );
    cpu.Reset();

    std::cout << (bool) 0x80 << std::endl;

    while ( true ) {
        printf("\n");

        if ( cpu.GetBreakFlag() ) {
            printf("\n----------BRK, reset------\n");
            cpu.Reset();
        }

        cpu.DisplayDebugInfos();
        cpu.DisplayStatus();
        cpu.Next();

        getchar();
        // printf("Ticks %d", cpu.GetCurrentClock());
    }
    // printf("Total %i\n", cpu.GetStatusFlag());
    // cpu.Display_Status();

    return 0;
}
