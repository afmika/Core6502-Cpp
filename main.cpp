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

    //std::string prog = "a2 03 a0 06 88 8c 15 00 ec 15 00 d0 f7";
    std::string prog = "a9 80 85 01 65 01";
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
        cpu.Next();
        cpu.DisplayDebugInfos();
        cpu.DisplayStatus();
        bus->DisplayMemory(0x0000, 0x0015);

        getchar();
        // printf("Ticks %d", cpu.GetCurrentClock());
    }
    // printf("Total %i\n", cpu.GetStatusFlag());
    // cpu.Display_Status();

    return 0;
}
