#include <bits/stdc++.h>
#include "component/CPU.h"

int main(int argc, const char * argv[]) {

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
    std::string final_prog = "";
    for (int  i = 1; i < argc; i++) {
        using namespace std;
        string temp( argv[i-1] );
        final_prog.append(temp + (i == argc ? ""s: " "s));
    }

    std::string prog = "a9 01 c9 02 d0 02 85 22 00";
    if ( argc == 1 ) {
        printf("Loading default test program...\n");
        final_prog = prog;
    } else {
        printf("Loading given program\n");
    }

    bus->loadProgram(final_prog);

    printf("Program Size %i bits | %i Chuncks", bus->memSize(), bus->memSize() / 8);

    CPU::Core6502 cpu;
    cpu.Connect( bus );
    cpu.Reset();

    std::cout << (bool) 0x80 << std::endl;


    // step by 
    while ( true ) {
        printf("\n");

        if ( cpu.GetBreakFlag() ) {
            printf("\n----------BRK, reset------\n");
            cpu.Reset();
        }
        cpu.Next();
        cpu.DisplayDebugInfos();
        cpu.DisplayStatus();
        bus->DisplayMemory(0x0000, 0x00FF / 4);

        getchar();
        // printf("Ticks %d", cpu.GetCurrentClock());
    }

    // continuous
    /*
    while ( true ) {
        cpu.Next();
        if ( cpu.GetBreakFlag() ) {
            cpu.DisplayDebugInfos();
            cpu.DisplayStatus();
            bus->DisplayMemory(0x0000, 0x00FF / 4);
            printf("\n----------BRK, reset------\n");
            cpu.Reset();
            getchar();
        }
    }
    */
    return 0;
}
