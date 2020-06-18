#pragma once
#include <bits/stdc++.h>

/**
 * @author afmika
 * MOS6502 - Emulator
 * June 2020
 */

namespace CPU {
    typedef struct BUS {
        uint16_t r_min;
        uint16_t r_max;
        std::map<uint16_t, uint8_t> MEMORY;

        BUS (uint16_t r_min, uint16_t r_max, bool initialise) {
            this->r_min = r_min;
            this->r_max = r_max;
            if ( initialise ) {
                for (uint16_t addr = r_min; addr <= r_max; addr++ ) {
                    MEMORY[addr] = 0x00;
                }
            }
        }

        void loadProgram(std::string prog) {
            std::stringstream s;
            s << prog;
            uint16_t mem_index = 0x0000;
            while ( ! s.eof() ) {
                std::string token;
                s >> token;
                MEMORY[mem_index++] = (uint8_t) std::stoul(token, nullptr, 16);
            }
        }

        size_t memSize()
        {
            return MEMORY.size() * 8;
        }

        void checkRange(uint16_t addr)
        {
            if ( ! (addr >= r_min && addr <= r_max ) ) {
                throw "INVALID ADDRESS RANGE!";
            }
        }
        uint8_t read(uint16_t addr)
        {
            checkRange(addr);
            return MEMORY[addr];
        }
        void write(uint16_t addr, uint8_t data)
        {
            checkRange(addr);
            MEMORY[addr] = data;
        }
    } BUS;



    // CPU Core
    class Core6502 {
        public:
            // ctor / dtor
            Core6502();
            virtual ~Core6502();

            // debugging
            int GetCurrentClock();
            void DisplayStatus();
            void DisplayDebugInfos();
            std::string StringifyAddressMode(uint16_t instr_addr);

            /**
             * CPU Status flags
             */
            bool GetNegativeFlag    () const; // N
            bool GetOverFlowFlag    () const; // V
            bool GetBreakFlag       () const; // B
            bool GetDecimalModeFlag () const; // D
            bool GetIRQFlag         () const; // I
            bool GetZeroFlag        () const; // Z
            bool GetCarryFlag       () const; // C

            uint8_t GetStatusFlag   () const; // = Sum[flag[i] * 2 ^ 7-i ]


            // Handles the CPU Instructions
            void runInstructions(std::vector<uint16_t> instructions);

            /**
             * Handles the CPU status flags
             * N | V |   | B | D | I | Z | C
             */
            void SetNegativeFlag    (bool value); // N
            void SetOverFlowFlag    (bool value); // V
            void SetBreakFlag       (bool value); // B
            void SetDecimalModeFlag (bool value); // D
            void SetIRQFlag         (bool value); // I
            void SetZeroFlag        (bool value); // Z
            void SetCarryFlag       (bool value); // C


            /**
             * Connects the CPU with an external component (ex : a RAM)
             * @todo
             */
             void Connect(BUS * bus);
             void Reset();



            // Instructions
            typedef struct Instr {
                std::string name;
                uint8_t (CPU::Core6502::*run)() = nullptr;
                uint8_t (CPU::Core6502::*addrmode)() = nullptr;
                uint8_t n_clocks;
                uint8_t n_bytes; // just keeping this one as a suplementary information
            } Instr;

            /**
             * Instruction map
             */
            std::map<uint8_t, Instr> opcodes;

            /**
             * 6502's legal instructions
             * @todo
             */
            uint8_t ADC(); // add with carry
            uint8_t AND(); // and (with accumulator)
            uint8_t ASL(); // arithmetic shift left
            uint8_t BCC(); // branch on carry clear
            uint8_t BCS(); // branch on carry set
            uint8_t BEQ(); // branch on equal (zero set)
            uint8_t BIT(); // bit test
            uint8_t BMI(); // branch on minus (negative set)
            uint8_t BNE(); // branch on not equal (zero clear)
            uint8_t BPL(); // branch on plus (negative clear)
            uint8_t BRK(); // break / interrupt
            uint8_t BVC(); // branch on overflow clear
            uint8_t BVS(); // branch on overflow set
            uint8_t CLC(); // clear carry
            uint8_t CLD(); // clear decimal
            uint8_t CLI(); // clear interrupt disable
            uint8_t CLV(); // clear overflow
            uint8_t CMP(); // compare (with accumulator)
            uint8_t CPX(); // compare with X
            uint8_t CPY(); // compare with Y
            uint8_t DEC(); // decrement
            uint8_t DEX(); // decrement X
            uint8_t DEY(); // decrement Y
            uint8_t EOR(); // exclusive or (with accumulator)
            uint8_t INC(); // increment
            uint8_t INX(); // increment X
            uint8_t INY(); // increment Y
            uint8_t JMP(); // jump
            uint8_t JSR(); // jump subroutine
            uint8_t LDA(); // load accumulator
            uint8_t LDX(); // load X
            uint8_t LDY(); // load Y
            uint8_t LSR(); // logical shift right
            uint8_t NOP(); // no operation
            uint8_t ORA(); // or with accumulator
            uint8_t PHA(); // push accumulator
            uint8_t PHP(); // push processor status (SR)
            uint8_t PLA(); // pull accumulator
            uint8_t PLP(); // pull processor status (SR)
            uint8_t ROL(); // rotate left
            uint8_t ROR(); // rotate right
            uint8_t RTI(); // return from interrupt
            uint8_t RTS(); // return from subroutine
            uint8_t SBC(); // subtract with carry
            uint8_t SEC(); // set carry
            uint8_t SED(); // set decimal
            uint8_t SEI(); // set interrupt disable
            uint8_t STA(); // store accumulator
            uint8_t STX(); // store X
            uint8_t STY(); // store Y
            uint8_t TAX(); // transfer accumulator to X
            uint8_t TAY(); // transfer accumulator to Y
            uint8_t TSX(); // transfer stack pointer to X
            uint8_t TXA(); // transfer X to accumulator
            uint8_t TXS(); // transfer X to stack pointer
            uint8_t TYA(); // transfer Y to accumulator

            /**
             * Handles the addressing mode of all instructions
             * @todo
             */

            uint8_t MODE_ACC (); // Accumulator

            uint8_t MODE_ABS (); // Absolute
            uint8_t MODE_ABX (); // Absolute X-indexed
            uint8_t MODE_ABY (); // Absolute Y-indexed

            uint8_t MODE_IMM (); // Immediate
            uint8_t MODE_IMP (); // Implied

            uint8_t MODE_IND (); // Indirect
            uint8_t MODE_INX (); // X-Indexed, indirect
            uint8_t MODE_INY (); // indirect, Y-indexed

            uint8_t MODE_REL (); // Relative

            uint8_t MODE_ZRO (); // Zeropage
            uint8_t MODE_ZRX (); // Zeropage X
            uint8_t MODE_ZRY (); // Zeropage Y

            uint8_t NONE     (); // Illegal

            /**
             * Handles the CPU clock (1 clock => need to point at another addr)
             */
            void Next();

        private:

            /**
             * CPU REGISTERS
             */
            // the program counter allows us to read to read the program inside
            // our virtual memory
            uint16_t PROG_COUNTER = 0x0000; // 2 Bytes
			uint8_t STACK_PTR     = 0x00;   // 1 Byte

            uint8_t ACCUMULATOR = 0x00;
            uint8_t X           = 0x00;
            uint8_t Y           = 0x00;


            /**
             * CLOCK CYCLES
             */
            uint8_t  CLOCK     = 0x00;

            // helpers
            uint8_t  CUR_VALUE = 0x00;   // stores a temporary value
            uint16_t ADDR_ABS  = 0x0000; // stores a temporary address for abs instr
            uint16_t ADDR_REL  = 0x0000; // stores a temporary address for relative instr

            // debugging
            uint8_t CUR_OPCODE = 0x00;
            std::string CUR_MODE = "";
            std::string CUR_INSTR = "";


            /**
             * CPU OUTPUTS
             */
            BUS * bus;
            // R/W the data on the bus
            uint16_t read(uint16_t addr);
            uint16_t write(uint16_t addr, uint8_t data);


            /**
             * CPU STATUS FLAG
             * In fact they are all 1 bit each
             * (They can be contained inside a 8 bits number)
             */
            bool NEG_FLAG = false;
            bool V_FLAG   = false;
            bool BRK_FLAG = false;
            bool D_FLAG   = false;
            bool IRQ_FLAG = false;
            bool Z_FLAG   = false;
            bool C_FLAG   = false;
    };
};
