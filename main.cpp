#include <bits/stdc++.h>
#include "include/CPU.h"

int main() {

    CPU::BUS* bus = new CPU::BUS(0x0000, 0xffff, false);

    // loads a program inside the virtual RAM
    /*
    bus->MEMORY = {
        // ADC #3
        {0x0000, 0xA9},
        {0x0001, 0x03},
        // LDA #$FF
        {0x0002, 0x69},
        {0x0003, 0xFF}
    };
    */

    std::string prog = "69 03 A9 FF";
    bus->loadProgram(prog);

    CPU::Core6502 cpu;
    cpu.Connect( bus );

    int c = 0;
    while ( c < 20 ) {
        cpu.Next();
        cpu.DisplayDebugInfos();
        cpu.DisplayRegisters();
        cpu.DisplayStatus();
        printf("\n");
        c++;
    }

    // printf("Total %i\n", cpu.GetStatusFlag());
    // cpu.Display_Status();

    return 0;
}
