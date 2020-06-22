#include <bits/stdc++.h>
#include "component/CPU.h"

int main(int argc, const char * argv[]) {
    std::string final_prog = "";
	std::string dg_flag = "-d";
	bool debug_mode = false;
    for (int  i = 1; i < argc; i++) {
        std::string temp( argv[i] );
		if ( temp.compare(dg_flag) == 0 && i == 1 ) {
			debug_mode = true;
		} else {
			final_prog.append(temp + (i + 1 == argc ? "": " "));
		}
    }
	
    std::string prog = "a2 02 a0 04 8e 24 00 6d 24 00 8d 25 00 88 d0 f7";
    if ( argc == 1 ) {
        printf("Loading default test program...\n");
        final_prog = prog;
    } else {
        printf("Loading given program...\n");
        printf("----------\n");
        printf("%s\n", final_prog.c_str());
        printf("----------\n");
    }

    CPU::BUS* bus = new CPU::BUS(0x0000, 0xffff, false);
    bus->loadProgram(final_prog);

    printf("Program Size %i bits | %i Chuncks\n", bus->memSize(), bus->memSize() / 8);

    CPU::Core6502 cpu;
	// cpu.DefineProgramCounter(0x0600);
    cpu.Connect( bus );
    cpu.Reset();
	
	if ( debug_mode ) {
	    // step by step
		while ( true ) {
			printf("\n");
			if ( cpu.GetBreakFlag() ) {
				printf("\n----------[---- STOP - BRK - EXECUTION DONE ----]------\n");
				cpu.Reset();
				break;
			} else {
				cpu.Next();
				cpu.DisplayDebugInfos();
				cpu.DisplayStatus();
				bus->DisplayMemory(0x0000, 0x00FF / 4);  
				bus->DisplayStackMemory( cpu.GetStackPtrvalue() );
			}
			getchar();
		}
		return 0;
	}
	
    while ( true ) {
        cpu.Next();
        if ( cpu.GetBreakFlag() ) {
            cpu.DisplayDebugInfos();
            cpu.DisplayStatus();
            bus->DisplayMemory(0x0000, 0x00FF / 4);
            bus->DisplayStackMemory( cpu.GetStackPtrvalue() );
            printf("\n[---- STOP - BRK - EXECUTION DONE ----]\n");
            cpu.Reset();
            getchar();
            return 0;
        }
    }
    return 0;
}
