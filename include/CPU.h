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
            void SetDisableFlag (uint8_t pos);
            void SetEnableFlag  (uint8_t pos);
            void SetStatusFlag  (bool value, uint8_t pos);

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
                void (CPU::Core6502::*run)() = nullptr;
                void (CPU::Core6502::*addrmode)() = nullptr;
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
            void ADC(); // add with carry
            void AND(); // and (with accumulator)
            void ASL(); // arithmetic shift left
            void BCC(); // branch on carry clear
            void BCS(); // branch on carry set
            void BEQ(); // branch on equal (zero set)
            void BIT(); // bit test
            void BMI(); // branch on minus (negative set)
            void BNE(); // branch on not equal (zero clear)
            void BPL(); // branch on plus (negative clear)
            void BRK(); // break / interrupt
            void BVC(); // branch on overflow clear
            void BVS(); // branch on overflow set
            void CLC(); // clear carry
            void CLD(); // clear decimal
            void CLI(); // clear interrupt disable
            void CLV(); // clear overflow
            void CMP(); // compare (with accumulator)
            void CPX(); // compare with X
            void CPY(); // compare with Y
            void DEC(); // decrement
            void DEX(); // decrement X
            void DEY(); // decrement Y
            void EOR(); // exclusive or (with accumulator)
            void INC(); // increment
            void INX(); // increment X
            void INY(); // increment Y
            void JMP(); // jump
            void JSR(); // jump subroutine
            void LDA(); // load accumulator
            void LDX(); // load X
            void LDY(); // load Y
            void LSR(); // logical shift right
            void NOP(); // no operation
            void ORA(); // or with accumulator
            void PHA(); // push accumulator
            void PHP(); // push processor status (SR)
            void PLA(); // pull accumulator
            void PLP(); // pull processor status (SR)
            void ROL(); // rotate left
            void ROR(); // rotate right
            void RTI(); // return from interrupt
            void RTS(); // return from subroutine
            void SBC(); // subtract with carry
            void SEC(); // set carry
            void SED(); // set decimal
            void SEI(); // set interrupt disable
            void STA(); // store accumulator
            void STX(); // store X
            void STY(); // store Y
            void TAX(); // transfer accumulator to X
            void TAY(); // transfer accumulator to Y
            void TSX(); // transfer stack pointer to X
            void TXA(); // transfer X to accumulator
            void TXS(); // transfer X to stack pointer
            void TYA(); // transfer Y to accumulator

            /**
             * Handles the addressing mode of all instructions
             * @todo
             */

            void MODE_ACC (); // Accumulator

            void MODE_ABS (); // Absolute
            void MODE_ABX (); // Absolute X-indexed
            void MODE_ABY (); // Absolute Y-indexed

            void MODE_IMM (); // Immediate
            void MODE_IMP (); // Implied

            void MODE_IND (); // Indirect
            void MODE_INX (); // X-Indexed, indirect
            void MODE_INY (); // indirect, Y-indexed

            void MODE_REL (); // Relative

            void MODE_ZRO (); // Zeropage
            void MODE_ZRX (); // Zeropage X
            void MODE_ZRY (); // Zeropage Y

            void NONE     (); // Illegal

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
            uint8_t STATUS_FLAG = (1 << 5);
    };
};
