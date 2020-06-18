#include <bits/stdc++.h>
#include "include/CPU.h"

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

    std::string prog = "A9 03 A2 02 A0 03 69 FF";
    bus->loadProgram(prog);

    printf("Program Size %i bits | %i Chuncks", bus->memSize(), bus->memSize() / 8);

    CPU::Core6502 cpu;
    cpu.Connect( bus );
    cpu.Reset();

    int c = 0;
    while ( c < 20 ) {
        if ( cpu.GetCurrentClock() == 0 ) {
            printf("\n");
            cpu.DisplayDebugInfos();
            cpu.DisplayStatus();
        }
        cpu.Next();
        // printf("Ticks %d", cpu.GetCurrentClock());
        c++;
    }

    // printf("Total %i\n", cpu.GetStatusFlag());
    // cpu.Display_Status();

    return 0;
}
