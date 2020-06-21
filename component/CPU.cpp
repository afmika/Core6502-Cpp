#include "CPU.h"

/**
 * @author afmika
 * MOS6502 - Emulator
 * June 2020
 */

CPU::Core6502::Core6502()
{
    this->Reset();

    // opcodes[addr] = name, instr, addrmode, n_clocks, n_bytes
    // ??? = illegal opcode
    opcodes[0x00] = {"BRK", CPU::Core6502::BRK, CPU::Core6502::MODE_IMM, 7} ;
    opcodes[0x01] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0x02] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x03] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x04] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x05] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x06] = {"ASL", CPU::Core6502::ASL, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0x07] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x08] = {"PHP", CPU::Core6502::PHP, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x09] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0x0a] = {"ASL", CPU::Core6502::ASL, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x0b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x0c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x0d] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x0e] = {"ASL", CPU::Core6502::ASL, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0x0f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x10] = {"BPL", CPU::Core6502::BPL, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0x11] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0x12] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x13] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x14] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x15] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x16] = {"ASL", CPU::Core6502::ASL, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0x17] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x18] = {"CLC", CPU::Core6502::CLC, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x19] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0x1a] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x1b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x1c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x1d] = {"ORA", CPU::Core6502::ORA, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0x1e] = {"ASL", CPU::Core6502::ASL, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0x1f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x20] = {"JSR", CPU::Core6502::JSR, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0x21] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0x22] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x23] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x24] = {"BIT", CPU::Core6502::BIT, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x25] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x26] = {"ROL", CPU::Core6502::ROL, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0x27] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x28] = {"PLP", CPU::Core6502::PLP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x29] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0x2a] = {"ROL", CPU::Core6502::ROL, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x2b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x2c] = {"BIT", CPU::Core6502::BIT, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x2d] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x2e] = {"ROL", CPU::Core6502::ROL, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0x2f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x30] = {"BMI", CPU::Core6502::BMI, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0x31] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0x32] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x33] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x34] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x35] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x36] = {"ROL", CPU::Core6502::ROL, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0x37] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x38] = {"SEC", CPU::Core6502::SEC, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x39] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0x3a] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x3b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x3c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x3d] = {"AND", CPU::Core6502::AND, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0x3e] = {"ROL", CPU::Core6502::ROL, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0x3f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x40] = {"RTI", CPU::Core6502::RTI, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x41] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0x42] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x43] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x44] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x45] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x46] = {"LSR", CPU::Core6502::LSR, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0x47] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x48] = {"PHA", CPU::Core6502::PHA, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x49] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0x4a] = {"LSR", CPU::Core6502::LSR, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x4b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x4c] = {"JMP", CPU::Core6502::JMP, CPU::Core6502::MODE_ABS, 3} ;
    opcodes[0x4d] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x4e] = {"LSR", CPU::Core6502::LSR, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0x4f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x50] = {"BVC", CPU::Core6502::BVC, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0x51] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0x52] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x53] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x54] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x55] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x56] = {"LSR", CPU::Core6502::LSR, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0x57] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x58] = {"CLI", CPU::Core6502::CLI, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x59] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0x5a] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x5b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x5c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x5d] = {"EOR", CPU::Core6502::EOR, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0x5e] = {"LSR", CPU::Core6502::LSR, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0x5f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x60] = {"RTS", CPU::Core6502::RTS, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x61] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0x62] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x63] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x64] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x65] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x66] = {"ROR", CPU::Core6502::ROR, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0x67] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x68] = {"PLA", CPU::Core6502::PLA, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x69] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0x6a] = {"ROR", CPU::Core6502::ROR, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x6b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x6c] = {"JMP", CPU::Core6502::JMP, CPU::Core6502::MODE_IND, 5} ;
    opcodes[0x6d] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x6e] = {"ROR", CPU::Core6502::ROR, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0x6f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x70] = {"BVS", CPU::Core6502::BVS, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0x71] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0x72] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x73] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0x74] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x75] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x76] = {"ROR", CPU::Core6502::ROR, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0x77] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x78] = {"SEI", CPU::Core6502::SEI, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x79] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0x7a] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x7b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x7c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x7d] = {"ADC", CPU::Core6502::ADC, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0x7e] = {"ROR", CPU::Core6502::ROR, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0x7f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0x80] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x81] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0x82] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x83] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x84] = {"STY", CPU::Core6502::STY, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x85] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x86] = {"STX", CPU::Core6502::STX, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0x87] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0x88] = {"DEY", CPU::Core6502::DEY, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x89] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x8a] = {"TXA", CPU::Core6502::TXA, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x8b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x8c] = {"STY", CPU::Core6502::STY, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x8d] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x8e] = {"STX", CPU::Core6502::STX, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0x8f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x90] = {"BCC", CPU::Core6502::BCC, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0x91] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ZRY, 6} ;
    opcodes[0x92] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x93] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0x94] = {"STY", CPU::Core6502::STY, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x95] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0x96] = {"STX", CPU::Core6502::STX, CPU::Core6502::MODE_ZRY, 4} ;
    opcodes[0x97] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0x98] = {"TYA", CPU::Core6502::TYA, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x99] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ABY, 5} ;
    opcodes[0x9a] = {"TXS", CPU::Core6502::TXS, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0x9b] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x9c] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x9d] = {"STA", CPU::Core6502::STA, CPU::Core6502::MODE_ABX, 5} ;
    opcodes[0x9e] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0x9f] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0xa0] = {"LDY", CPU::Core6502::LDY, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xa1] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0xa2] = {"LDX", CPU::Core6502::LDX, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xa3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0xa4] = {"LDY", CPU::Core6502::LDY, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xa5] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xa6] = {"LDX", CPU::Core6502::LDX, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xa7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 3} ;
    opcodes[0xa8] = {"TAY", CPU::Core6502::TAY, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xa9] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xaa] = {"TAX", CPU::Core6502::TAX, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xab] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xac] = {"LDY", CPU::Core6502::LDY, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xad] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xae] = {"LDX", CPU::Core6502::LDX, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xaf] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xb0] = {"BCS", CPU::Core6502::BCS, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0xb1] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0xb2] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xb3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0xb4] = {"LDY", CPU::Core6502::LDY, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0xb5] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0xb6] = {"LDX", CPU::Core6502::LDX, CPU::Core6502::MODE_ZRY, 4} ;
    opcodes[0xb7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xb8] = {"CLV", CPU::Core6502::CLV, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xb9] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0xba] = {"TSX", CPU::Core6502::TSX, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xbb] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xbc] = {"LDY", CPU::Core6502::LDY, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0xbd] = {"LDA", CPU::Core6502::LDA, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0xbe] = {"LDX", CPU::Core6502::LDX, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0xbf] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xc0] = {"CPY", CPU::Core6502::CPY, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xc1] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0xc2] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xc3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0xc4] = {"CPY", CPU::Core6502::CPY, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xc5] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xc6] = {"DEC", CPU::Core6502::DEC, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0xc7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0xc8] = {"INY", CPU::Core6502::INY, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xc9] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xca] = {"DEX", CPU::Core6502::DEX, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xcb] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xcc] = {"CPY", CPU::Core6502::CPY, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xcd] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xce] = {"DEC", CPU::Core6502::DEC, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0xcf] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0xd0] = {"BNE", CPU::Core6502::BNE, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0xd1] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0xd2] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xd3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0xd4] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xd5] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0xd6] = {"DEC", CPU::Core6502::DEC, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0xd7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0xd8] = {"CLD", CPU::Core6502::CLD, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xd9] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0xda] = {"NOP", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xdb] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0xdc] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xdd] = {"CMP", CPU::Core6502::CMP, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0xde] = {"DEC", CPU::Core6502::DEC, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0xdf] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0xe0] = {"CPX", CPU::Core6502::CPX, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xe1] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_INX, 6} ;
    opcodes[0xe2] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xe3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0xe4] = {"CPX", CPU::Core6502::CPX, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xe5] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ZRO, 3} ;
    opcodes[0xe6] = {"INC", CPU::Core6502::INC, CPU::Core6502::MODE_ZRO, 5} ;
    opcodes[0xe7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 5} ;
    opcodes[0xe8] = {"INX", CPU::Core6502::INX, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xe9] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_IMM, 2} ;
    opcodes[0xea] = {"NOP", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xeb] = {"???", CPU::Core6502::SBC, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xec] = {"CPX", CPU::Core6502::CPX, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xed] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ABS, 4} ;
    opcodes[0xee] = {"INC", CPU::Core6502::INC, CPU::Core6502::MODE_ABS, 6} ;
    opcodes[0xef] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0xf0] = {"BEQ", CPU::Core6502::BEQ, CPU::Core6502::MODE_REL, 2} ;
    opcodes[0xf1] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ZRY, 5} ;
    opcodes[0xf2] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xf3] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 8} ;
    opcodes[0xf4] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xf5] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ZRX, 4} ;
    opcodes[0xf6] = {"INC", CPU::Core6502::INC, CPU::Core6502::MODE_ZRX, 6} ;
    opcodes[0xf7] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 6} ;
    opcodes[0xf8] = {"SED", CPU::Core6502::SED, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xf9] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ABY, 4} ;
    opcodes[0xfa] = {"NOP", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 2} ;
    opcodes[0xfb] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7} ;
    opcodes[0xfc] = {"???", CPU::Core6502::NOP, CPU::Core6502::MODE_IMP, 4} ;
    opcodes[0xfd] = {"SBC", CPU::Core6502::SBC, CPU::Core6502::MODE_ABX, 4} ;
    opcodes[0xfe] = {"INC", CPU::Core6502::INC, CPU::Core6502::MODE_ABX, 7} ;
    opcodes[0xff] = {"???", CPU::Core6502::NONE, CPU::Core6502::MODE_IMP, 7};
}

CPU::Core6502::~Core6502()
{

}

int CPU::Core6502::GetCurrentClock()
{
    return CLOCK;
}

void CPU::Core6502::DisplayStatus()
{
    /*
     * REGISTERS
     */
    const char * row = "+----+----+----+----------------+";
    const char * str = "| AC | XR | YR |   STACK_PTR    |";
    const char * vrow= "+-------------------------------+";
    printf("%s\n%s\n%s\n", row, str, row);
    printf("| %02x | %02x | %02x |          %02x    |\n", ACCUMULATOR, X, Y, STACK_PTR);
    printf("%s\n", vrow);

    /*
     * STATUS
     * 7   6   5   4   3   2   1   0
     * N | V |   | B | D | I | Z | C
     */
    uint8_t reg = GetStatusFlag();
    uint8_t k = 0;
    const char * row1 = "+---+---+---+---+---+---+---+---+";
    const char * str1 = "| N | V |   | B | D | I | Z | C |\n";

    printf("%s", str1);
    printf("%s\n", row1);
    printf("|");
    while ( k < 8 ) {
        printf(" %i |", (reg >> (7-k) ) & 1);
        k++;
    }
    printf("\n%s", row1);
    /*
     * PROGRAM COUNTER
     */
    printf("\n");
    printf("| PROG_COUNTER            %04x  |\n", PROG_COUNTER);
    printf("%s\n", vrow);
    printf("| CLOCK_LEFT              %04x  |\n", GetCurrentClock());
    printf("%s\n", vrow);
}

void CPU::Core6502::DisplayDebugInfos()
{
    printf("OPCODE %04x | %s [%s]\n", CUR_OPCODE, CUR_INSTR.c_str(), CUR_MODE.c_str());
    if ( CURRENT_ADDRMODE != &MODE_IMP) {
        printf("=> %s $%04x (%s)\n", CUR_INSTR.c_str(), ARGUMENT, CUR_MODE.c_str());
    } else {
        printf("=> %s ---- (%s)\n", CUR_INSTR.c_str(), CUR_MODE.c_str());
    }
}

std::string CPU::Core6502::StringifyAddressMode(uint16_t instr_addr)
{
    if ( opcodes[instr_addr].addrmode == &MODE_ACC ){ return "ACC"; } // Accumulator
    if ( opcodes[instr_addr].addrmode == &MODE_ABS ){ return "ABS"; } // Absolute
    if ( opcodes[instr_addr].addrmode == &MODE_ABX ){ return "ABX"; } // Absolute X-indexed
    if ( opcodes[instr_addr].addrmode == &MODE_ABY ){ return "ABY"; } // Absolute Y-indexed
    if ( opcodes[instr_addr].addrmode == &MODE_IMM ){ return "IMM"; } // Immediate
    if ( opcodes[instr_addr].addrmode == &MODE_IMP ){ return "IMP"; } // Implied
    if ( opcodes[instr_addr].addrmode == &MODE_IND ){ return "IND"; } // Indirect
    if ( opcodes[instr_addr].addrmode == &MODE_INX ){ return "INX"; } // X-Indexed, indirect
    if ( opcodes[instr_addr].addrmode == &MODE_INY ){ return "INY"; } // indirect, Y-indexed
    if ( opcodes[instr_addr].addrmode == &MODE_REL ){ return "REL"; } // Relative
    if ( opcodes[instr_addr].addrmode == &MODE_ZRO ){ return "ZRO"; } // Zeropage
    if ( opcodes[instr_addr].addrmode == &MODE_ZRX ){ return "ZRX"; } // Zeropage X
    if ( opcodes[instr_addr].addrmode == &MODE_ZRY ){ return "ZRY"; } // Zeropage Y
    return "---"; // Illegal
}


void CPU::Core6502::Next () // CLOCK
{
    uint8_t instr_addr = read(PROG_COUNTER++);      // gets the instr loaded in the memory
    CUR_OPCODE = instr_addr;

    // printf("%02x\n", instr_addr);

    CLOCK += opcodes[instr_addr].n_clocks;          // gets the number of cycle we need

    (this->*opcodes[instr_addr].addrmode) ();       // initializes some variables according to the addrmode
    
    // addr mode check
    CURRENT_ADDRMODE = opcodes[instr_addr].addrmode;
    if ( CURRENT_ADDRMODE != &MODE_IMP ) {
        // ARGUMENT contains the addr_abs
        BEF_READING = ARGUMENT; // there are cases where this is useful (ex: if the instr requires writting)
        ARGUMENT = read(ARGUMENT);
    }
    // end addr mode check

    (this->*opcodes[instr_addr].run) ();            // runs the instruction

    // debug
    CUR_INSTR  = opcodes[instr_addr].name;
    CUR_MODE   = StringifyAddressMode( instr_addr );
}

/**
 * CPU Status flags
 */
bool CPU::Core6502::GetNegativeFlag () const // N
{
    return (STATUS_FLAG >> 7) & 1;
}

bool CPU::Core6502::GetOverFlowFlag () const // V
{
    return (STATUS_FLAG >> 6) & 1;
}

bool CPU::Core6502::GetBreakFlag () const // B
{
    return (STATUS_FLAG >> 4) & 1;
}

bool CPU::Core6502::GetDecimalModeFlag ()  const // D
{
    return (STATUS_FLAG >> 3) & 1;
}

bool CPU::Core6502::GetIRQFlag () const // I
{
    return (STATUS_FLAG >> 2) & 1;
}

bool CPU::Core6502::GetZeroFlag () const // Z
{
    return (STATUS_FLAG >> 1) & 1;
}

bool CPU::Core6502::GetCarryFlag () const // C
{
    return (STATUS_FLAG >> 0) & 1;
}

uint8_t CPU::Core6502::GetStatusFlag () const
{
     return STATUS_FLAG;
}


/**
 * Handles the CPU status flags
 * N | V |   | B | D | I | Z | C
 */
void CPU::Core6502::SetEnableFlag(uint8_t pos)
{
    bool is_set = ( STATUS_FLAG >> pos ) & 1;
    if ( ! is_set ) {
        STATUS_FLAG |= (1 << pos);
    }
}

void CPU::Core6502::SetDisableFlag(uint8_t pos)
{
    bool is_set = ( STATUS_FLAG >> pos ) & 1;
    if ( is_set ) {
        STATUS_FLAG ^= (1 << pos);
    }
}

void CPU::Core6502::SetStatusFlag(bool value, uint8_t pos)
{
    if ( value ) SetEnableFlag (pos);
    else         SetDisableFlag(pos);
}


void CPU::Core6502::SetNegativeFlag (bool value) // N
{
    SetStatusFlag (value, 7);
}

void CPU::Core6502::SetOverFlowFlag (bool value) // V
{
    SetStatusFlag (value, 6);
}

void CPU::Core6502::SetBreakFlag (bool value) // B
{
    SetStatusFlag (value, 4);
}

void CPU::Core6502::SetDecimalModeFlag (bool value) // D
{
    SetStatusFlag (value, 3);
}

void CPU::Core6502::SetIRQFlag (bool value) // I
{
    SetStatusFlag (value, 2);
}

void CPU::Core6502::SetZeroFlag (bool value) // Z
{
    SetStatusFlag (value, 1);
}

void CPU::Core6502::SetCarryFlag (bool value) // C
{
    SetStatusFlag (value, 0);
}

/**
 * BUS Connection
 */
void CPU::Core6502::Connect(BUS* bus)
{
    this->bus = bus;
}

void CPU::Core6502::Reset()
{
    PROG_COUNTER = 0x00;  // the current addr
    CLOCK        = 0x00;  // the current cycle count
    ARGUMENT     = 0x00;  // value fetched
    ARGUMENT     = 0x00;  // address fetched
    ADDR_REL     = 0x00;  // relative address fetched

    // debug variables
    CUR_INSTR    =   "";
    CUR_OPCODE   = 0x00;

    // basic registers
    ACCUMULATOR = 0x00;
    X           = 0x00;
    Y           = 0x00;
    STACK_PTR   = 0xff;

    STATUS_FLAG = (1 << 5);
}


/**
 * ADRESSING MODE
 */

/**
 *	A .... Accumulator OPC A operand is AC (implied single byte instruction)
 */
void CPU::Core6502::MODE_ACC () // Accumulator
{
    //  In this mode the instruction operates on data in the accumulator, so no operands are needed.
	ARGUMENT = ACCUMULATOR;
}

/**
 *	abs .... absolute OPC $LLHH operand is address $HHLL *
 */
void CPU::Core6502::MODE_ABS () // Absolute
{
    /*
    * The value given is the address (16-bits) of a memory location that
    * contains the 8-bit value to be used.  For example, STA $3E32 stores
    * the present value of the accumulator in memory location $3E32.
    */

    // 8bits Instr  + 16 bits = 3 bytes in total but we are interested in the two latest bytes
    // ex : $3E32 :: $HHLL
    // BUT... what we have inside the ram is actually reversed [... , LL, HH, ...]
    uint16_t LL = read(PROG_COUNTER++); // loads LL in the memory : 32
    uint16_t HH = read(PROG_COUNTER++); // loads HH in the memory : 3E

    // for our example we have ARGUMENT = 3E00 | 0032 which finally gives us 3E32
    ARGUMENT = ( HH << 8 ) | LL;
}

/**
 *	abs,X .... absolute, X-indexed OPC $LLHH,X operand is address; effective address is address incremented by X with carry **
 */
void CPU::Core6502::MODE_ABX () // Absolute X-indexed
{
    /*
    * The final address is found by taking the given address as a base and
    * adding the current value of the X or Y register to it as an offset.  So,
    * LDA $F453,X  where X contains 3
    */
    // same stuff as above
    // ex : $3E32 :: $HHLL
    uint16_t LL = read(PROG_COUNTER++);  // loads LL in the memory : 32
    uint16_t HH = read(PROG_COUNTER++);  // loads HH in the memory : 3E
    ARGUMENT = (( HH << 8 ) | LL) + X; // we are just using X as an offset

    // we need to add 1 more clock cycle if the page boundinary is crossed
    // for example $00FF + (X = 1) => $0100 (we need an additionnal cycle)
    // For our example the difference between $00FF and $0100 resides on the hibyte
    // we just need to check if the hibyte changed or not
    // (uint8_t) ( (ARGUMENT & 0xFF00) != (HH >> 8) );

    if ( (ARGUMENT >> 8) != HH ) CLOCK++;
}

/**
 *	abs,Y .... absolute, Y-indexed OPC $LLHH,Y operand is address; effective address is address incremented by Y with carry **
 */
void CPU::Core6502::MODE_ABY () // Absolute Y-indexed
{
    /*
    * The final address is found by taking the given address as a base and
    * adding the current value of the X or Y register to it as an offset.  So,
    * LDA $F453,Y  where Y contains 3
    */
    // same stuff as above
    // ex : $3E32 :: $HHLL
    uint16_t LL = read(PROG_COUNTER++);  // loads LL in the memory : 32
    uint16_t HH = read(PROG_COUNTER++);  // loads HH in the memory : 3E
    ARGUMENT = (( HH << 8 ) | LL) + Y; // we are just using Y as an offset

    // we need to add 1 more clock cycle if the page boundinary is crossed
    // for example $00FF + (Y = 1) => $0100 (we need an additionnal cycle)
    // For our example the difference between $00FF and $0100 resides on the hibyte
    // we just need to check if the hibyte changed or not
    // (uint8_t) ( (ARGUMENT & 0xFF00) != (HH >> 8) );

	if ((ARGUMENT >> 8) != HH) CLOCK++;
}

/**
 *	# .... immediate OPC #$BB operand is byte BB
 */
void CPU::Core6502::MODE_IMM () // Immediate
{
   /*
    * The value given is a number to be used immediately by the
    * instruction.  For example, LDA #$99 loads the value $99 into the
    * accumulator.
    */
    // we dont need the ram since the value given is already what we are going to use
    ARGUMENT = PROG_COUNTER++;
}

/**
 *	impl .... implied OPC operand implied
 */
void CPU::Core6502::MODE_IMP () // Implied
{
    // No operand addresses are required for this mode. They are implied by the instruction.
    // ARGUMENT = ACCUMULATOR;
    // or ARGUMENT = Y;
    // or ARGUMENT = X;
}

/**
 *	ind .... indirect OPC ($LLHH) operand is address; effective address is contents of word at address: C.w($HHLL)
 */
void CPU::Core6502::MODE_IND () // Indirect
{
    /*
     * Find the 16-bit address contained in the given location ( and the one
     * following).
     * Fetch the value stored at that address.
     */

    // This mode applies only to the JMP instruction - JuMP to new location. It is
    // indicated by parenthesis around the operand. The operand is the address of
    // the bytes whose value is the new location.

    // Ex : MEM [ 00F1 : 01, 00F1 : CC]
    // then JMP ($00F1) is equivalent to JMP $CC01

    // loads the two next bytes of instruction
    uint16_t LL       = read(PROG_COUNTER++);    // loads LL in the memory
    uint16_t HH       = read(PROG_COUNTER++);    // loads HH in the memory
    uint16_t ptr_addr = ( HH << 8 ) | LL;        // the memory address we are going to use

    // loads respectively the hibyte/hibyte stored inside the memory
    uint16_t LO       = read(ptr_addr);
    uint16_t HI       = 0x0000;

    // [NOTE] we can remove this condition
    // The original 6502 had this little bug :
    // if the lobyte of ptr_addr is equal to FF
    // then the +1 will be ignored
    // For example : $3EFF + 1 => $3E00 which is equal to $3EFF & $FF00

    // (ptr_addr & 0x00FF) == 0x00FF
    HI = LL == 0x00FF ? read(ptr_addr & 0xFF00) : read(ptr_addr + 1);

    // in our case operand is an address (2 bytes)
    ARGUMENT          = ( HI << 8 ) | LO;
}

/**
 *	X,ind .... X-indexed, indirect OPC ($LL,X) operand is zeropage address; effective address is word in (LL + X, LL + X + 1), inc. without carry: C.w($00LL + X)
 */
void CPU::Core6502::MODE_INX () // X-Indexed, indirect
{
    /*
    * In this mode a zer0-page address is added to the contents of the X-register
    * to give the address of the bytes holding the address of the operand. The
    * indirection is indicated by parenthesis in assembly language.
    *  eg.  LDA ($3E, X)
    *       $A1 $3E
    * Assume the following - byte      value
    *                        X-reg.    $05
    *                        $0043     $15
    *                        $0044     $24
    *                        $2415     $6E
    *
    * Then the instruction is executed by:
    * (i)   adding $3E and $05 = $0043
    * (ii)  getting address contained in bytes $0043, $0044 = $2415
    * (iii) loading contents of $2415 - i.e. $6E - into accumulator
    *
    * Note a) When adding the 1-byte address and the X-register, wrap around
    *       addition is used - i.e. the sum is always a zero-page address.
    *       eg. FF + 2 = 0001 not 0101 as you might expect.
    *       DON'T FORGET THIS WHEN EMULATING THIS MODE.
    *      b) Only the X register is used in this mode.
    *
    */

    // Basically, we take the zero page address,
    // add the value of the X register to it,
    // then use that to look up a two-byte address
    uint16_t temp_addr = read(PROG_COUNTER++); // no HHLL this time, we are using the zero page

    uint16_t ptr_adr   = temp_addr + X;
    uint16_t LL        = read( ptr_adr );
    uint16_t HH        = read( ptr_adr + 1 );

    ARGUMENT            = (HH << 8) | LL;
}

/**
 *	ind,Y .... indirect, Y-indexed OPC ($LL),Y operand is zeropage address; effective address is word in (LL, LL + 1) incremented by Y with carry: C.w($00LL) + Y
 */
void CPU::Core6502::MODE_INY () // indirect, Y-indexed
{
    /*
    * In this mode the contents of a zero-page address (and the following byte)
    * give the indirect address which is added to the contents of the Y-register
    * to yield the actual address of the operand. Again, inassembly language,
    * the instruction is indicated by parenthesis.
    *
    * eg.  LDA ($4C), Y
    * Note that the parenthesis are only around the 2nd byte of the instruction
    * since it is the part that does the indirection.
    * Assume the following -      byte       value
    *                             $004C      $00
    *                             $004D      $21
    *                             Y-reg.     $05
    *                             $2105      $6D
    *
    * Then the instruction above executes by:
    * (i)   getting the address in bytes $4C, $4D = $2100
    * (ii)  adding the contents of the Y-register = $2105
    * (111) loading the contents of the byte $2105 - i.e. $6D into the
    *     accumulator.
    * Note: only the Y-register is used in this mode.
    *
    */

    // Basically, we take the zero page address,
    // the zero page address is dereferenced,
    // then use that to look up a two-byte address
    // and the Y register is added to the resulting address
    uint8_t ptr_adr = read(PROG_COUNTER++);

    uint16_t LL = read( ptr_adr );
    uint16_t HH = read( ptr_adr + 1 );

    ARGUMENT     = ( HH << 8 ) | LL;
    ARGUMENT    += Y;

    // again if we encounter a new page
    if ( (ARGUMENT >> 8) != HH ) CLOCK++;
}

/**
 *	rel .... relative OPC $BB branch target is PC + signed offset BB ***
 */
void CPU::Core6502::MODE_REL () // Relative
{
    /*
    * This mode is used with Branch-on-Condition instructions. It is probably
    * the mode you will use most often. A 1 byte value is added to the program
    * counter, and the program continues execution from that address. The 1
    * byte number is treated as a signed number - i.e. if bit 7 is 1, the number
    * given byt bits 0-6 is negative; if bit 7 is 0, the number is positive. This
    * enables a branch displacement of up to 127 bytes in either direction.
    * eg  bit no.  7 6 5 4 3 2 1 0    signed value          unsigned value
    *     value    1 0 1 0 0 1 1 1    -39                   $A7
    *     value    0 0 1 0 0 1 1 1    +39                   $27
    * Instruction example:
    * BEQ $A7
    * $F0 $A7
    * This instruction will check the zero status bit. If it is set, 39 decimal
    * will be subtracted from the program counter and execution continues from
    * that address. If the zero status bit is not set, execution continues from
    * the following instruction.
    * Notes:  a) The program counter points to the start of the instruction
    * after the branch instruction before the branch displacement is added.
    * Remember to take this into account when calculating displacements.
    *       b) Branch-on-condition instructions work by checking the relevant
    * status bits in the status register. Make sure that they have been set or
    * unset as you want them. This is often done using a CMP instruction.
    *       c) If you find you need to branch further than 127 bytes, use the
    * opposite branch-on-condition and a JMP.
    */
    // Relative addressing is used for branching instructions.
    // These instructions take a single byte,
    // which is used as an offset from the following instruction.

    // Relative addressing mode is used by branch instructions (e.g. BEQ, BNE, etc.)
    // which contain a signed 8 bit relative offset (e.g. -128 to +127)
    // which is added to program counter if the condition is true.
    // As the program counter itself is incremented during instruction execution by two
    // the effective address range
    // for the target instruction must be with -126 to +129 bytes of the branch.

    // [NOTE] : we need to store the result inside ADDR_REL
    // and not ARGUMENT
    ADDR_REL = read(PROG_COUNTER++);

    // out of range
    // ex : -126 => 1
    if ( ADDR_REL & 0x0080 ) ADDR_REL |= 0xFF00;
}

/**
 *	zpg .... zeropage OPC $LL operand is zeropage address (hi-byte is zero, address = $00LL)
 */
void CPU::Core6502::MODE_ZRO () // Zeropage
{
    /*
    * The first 256 memory locations ($0000-00FF) are called "zero page".  The
    * next 256 instructions ($0100-01FF) are page 1, etc.  Instructions
    * making use of the zero page save memory by not using an extra $00 to
    * indicate the high part of the address.  For example,
    *   LDA $0023   -- works but uses an extra byte
    *   LDA $23     -- the zero page address
    */

    ARGUMENT = read( PROG_COUNTER++ ); // reading the value of the next address
    ARGUMENT &= 0x00FF;                // ex $0023 & $00FF = $23 , that's just what ZRO is about
}

/**
 *	zpg,X .... zeropage, X-indexed OPC $LL,X operand is zeropage address; effective address is address incremented by X without carry **
 */
void CPU::Core6502::MODE_ZRX () // Zeropage X
{
    // same thing as above but the value of the X register will servve as an offset
    ARGUMENT = read(PROG_COUNTER++) + X;
    ARGUMENT &= 0x00FF;
}

/**
 *	zpg,Y .... zeropage, Y-indexed OPC $LL,Y operand is zeropage address; effective address is address incremented by Y without carry **
 */
void CPU::Core6502::MODE_ZRY () // Zeropage Y
{
    // same thing as above but the value of the Y register will serve as an offset instead
    ARGUMENT = read(PROG_COUNTER++) + Y;
    ARGUMENT &= 0x00FF;
}

void CPU::Core6502::NONE () // Illegal
{
}


/**
 * CPU OUTPUTS
 */
// R/W the data on the bus
uint16_t CPU::Core6502::read(uint16_t addr)
{
    return bus->read(addr);
}
uint16_t CPU::Core6502::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
    return 0;
}







/**
 * 6502's 56 legal instructions with documentation
 */

/**
ADC  Add Memory to Accumulator with Carry
     A + M + C -> A, C                N Z C I D V
                                      + + + - - +
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     ADC #oper     69    2     2
     zeropage      ADC oper      65    2     3
     zeropage,X    ADC oper,X    75    2     4
     absolute      ADC oper      6D    3     4
     absolute,X    ADC oper,X    7D    3     4*
     absolute,Y    ADC oper,Y    79    3     4*
     (indirect,X)  ADC (oper,X)  61    2     6
     (indirect),Y  ADC (oper),Y  71    2     5*
*/
void CPU::Core6502::ADC ()
{
    // This instruction adds the contents of a memory location to the accumulator together with the carry bit. 
    // If overflow occurs the carry bit is set, this enables multiple byte addition to be performed.
    uint16_t a      = ACCUMULATOR;
    uint16_t op     = ARGUMENT;
    uint16_t c      = GetCarryFlag();

    // A + MSB + C
    uint16_t sum = a + op + c;

    SetCarryFlag (sum  > 0x00FF);    // ex FF + 1 => 00 (1 carry)

    uint8_t last_result = sum;
    SetZeroFlag (last_result == 0);  // if the last result is 0 it's true

    SetNegativeFlag(sum & 0x80);     // 8-th digit is set

    uint16_t V  = ~(a ^ op) & (a ^ sum);
    SetOverFlowFlag (V & 0x0080);    // Just checking the MSB

    ACCUMULATOR = sum;               // the 8-bits part only matters
}

/**
AND  AND Memory with Accumulator
     A AND M -> A                     N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     AND #oper     29    2     2
     zeropage      AND oper      25    2     3
     zeropage,X    AND oper,X    35    2     4
     absolute      AND oper      2D    3     4
     absolute,X    AND oper,X    3D    3     4*
     absolute,Y    AND oper,Y    39    3     4*
     (indirect,X)  AND (oper,X)  21    2     6
     (indirect),Y  AND (oper),Y  31    2     5*
*/
void CPU::Core6502::AND ()
{
    // A logical AND is performed, bit by bit, on the accumulator contents using the contents of a byte of memory.
    ACCUMULATOR    &= (uint8_t) ARGUMENT;

    SetZeroFlag    ( ACCUMULATOR == 0x00);
    SetNegativeFlag( ACCUMULATOR &  0x80);
    CLOCK++;
}

/**
ASL  Shift Left One Bit (Memory or Accumulator)
     C <- [76543210] <- 0             N Z C I D V
                                      + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     accumulator   ASL A         0A    1     2
     zeropage      ASL oper      06    2     5
     zeropage,X    ASL oper,X    16    2     6
     absolute      ASL oper      0E    3     6
     absolute,X    ASL oper,X    1E    3     7
*/
void CPU::Core6502::ASL ()
{
    // This operation shifts all the bits of the accumulator or memory contents one bit left. 
    // Bit 0 is set to 0 and bit 7 is placed in the carry flag. 
    // The effect of this operation is to multiply the memory contents by 2 (ignoring 2's complement considerations), 
    // setting the carry if the result will not fit in 8 bits.

    uint16_t res = ARGUMENT << 1;
    SetNegativeFlag( res &  0x80);
    SetZeroFlag    ( res & 0x00FF == 0x00);
    SetCarryFlag   ( res & 0xFF00 > 0xFF );

	if (CURRENT_ADDRMODE == &MODE_IMP) {
        ACCUMULATOR = res;   // if ARGUMENT == ACC
	} else {
		write(BEF_READING, res); //  if ARGUMENT == memory address
	}
}

/**
BCC  Branch on Carry Clear
     branch on C = 0                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BCC oper      90    2     2**
*/
void CPU::Core6502::BCC ()
{
    // If the carry flag is clear then add the relative displacement 
    // to the program counter to cause a branch to a new location.
    if ( !GetCarryFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BCS  Branch on Carry Set
     branch on C = 1                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BCS oper      B0    2     2**
*/
void CPU::Core6502::BCS ()
{
    // same as above
	if ( GetCarryFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BEQ  Branch on Result Zero
     branch on Z = 1                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BEQ oper      F0    2     2**
*/
void CPU::Core6502::BEQ ()
{
    if ( GetZeroFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BIT  Test Bits in Memory with Accumulator
     bits 7 and 6 of operand are transfered to bit 7 and 6 of SR (N,V);
     the zeroflag is set to the result of operand AND accumulator.
     A AND M, M7 -> N, M6 -> V        N Z C I D V
                                     M7 + - - - M6
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      BIT oper      24    2     3
     absolute      BIT oper      2C    3     4
*/
void CPU::Core6502::BIT ()
{
    // This instructions is used to test if one or more bits are set in a target memory location. 
    // The mask pattern in A is ANDed with the value in memory to set or clear the zero flag, 
    // but the result is not kept. 
    // Bits 7 and 6 of the value from memory are copied into the N and V flags.
	ARGUMENT &= ACCUMULATOR;
	SetZeroFlag     ((ARGUMENT & 0x00FF) == 0x00);
	SetNegativeFlag (ARGUMENT & (1 << 7));
	SetOverFlowFlag (ARGUMENT & (1 << 6));
}

/**
BMI  Branch on Result Minus
     branch on N = 1                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BMI oper      30    2     2**
*/
void CPU::Core6502::BMI ()
{
	if ( GetNegativeFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
    }
}

/**
BNE  Branch on Result not Zero
     branch on Z = 0                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BNE oper      D0    2     2**
*/
void CPU::Core6502::BNE ()
{
	if ( !GetZeroFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BPL  Branch on Result Plus
     branch on N = 0                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BPL oper      10    2     2**
*/
void CPU::Core6502::BPL ()
{
	if ( !GetNegativeFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BRK  Force Break
     interrupt,                       N Z C I D V
     push PC+2, push SR               - - - 1 - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       BRK           00    1     7
*/
void CPU::Core6502::BRK ()
{
    // The BRK instruction forces the generation of an interrupt request. 
    // 1- The program counter and processor status are pushed on the stack 
    // 2- then the IRQ interrupt vector at $FFFE/F is loaded into the PC 
    // 3- and the break flag in the status set to one.
    // [NOTE] : the stackptr range is [0100 - 01FF]

    // the program counter is pushed on the stack
	PROG_COUNTER++;
    uint8_t pc_LL = (uint8_t) PROG_COUNTER;
    uint8_t pc_HH = (uint8_t) PROG_COUNTER >> 8;

	write(0x0100 + STACK_PTR--, pc_HH );
    write(0x0100 + STACK_PTR--, pc_LL );
    
    
    // The processor status is pushed on the stack
	write(0x0100 + STACK_PTR--, GetStatusFlag() );

    // The IRQ interrupt vector at $FFFE/F is loaded into the PC
    uint16_t HH = read(0xFFFF) << 8;
    uint16_t LL = read(0xFFFE);
	PROG_COUNTER = HH | LL;

    // the BRQ flag is set to one
	SetBreakFlag(1);
}

/**
BVC  Branch on Overflow Clear
     branch on V = 0                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BVC oper      50    2     2**
*/
void CPU::Core6502::BVC ()
{
	if ( !GetOverFlowFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
BVS  Branch on Overflow Set
     branch on V = 1                  N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     relative      BVC oper      70    2     2**
*/
void CPU::Core6502::BVS ()
{
	if ( GetOverFlowFlag() ) {
		CLOCK++;
		ARGUMENT = PROG_COUNTER + ADDR_REL;
		if( (ARGUMENT & 0xFF00) != (PROG_COUNTER & 0xFF00) ) CLOCK++;
		PROG_COUNTER = ARGUMENT;
	}
}

/**
CLC  Clear Carry Flag
     0 -> C                           N Z C I D V
                                      - - 0 - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       CLC           18    1     2
*/
void CPU::Core6502::CLC ()
{
    SetCarryFlag(0);
}

/**
CLD  Clear Decimal Mode
     0 -> D                           N Z C I D V
                                      - - - - 0 -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       CLD           D8    1     2
*/
void CPU::Core6502::CLD ()
{
    SetDecimalModeFlag(0);
}

/**
CLI  Clear Interrupt Disable Bit
     0 -> I                           N Z C I D V
                                      - - - 0 - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       CLI           58    1     2
*/
void CPU::Core6502::CLI ()
{
    SetIRQFlag(0);
}

/**
CLV  Clear Overflow Flag
     0 -> V                           N Z C I D V
                                      - - - - - 0
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       CLV           B8    1     2
*/
void CPU::Core6502::CLV ()
{
    SetOverFlowFlag(0);
}

/**
CMP  Compare Memory with Accumulator
     A - M                            N Z C I D V
                                    + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     CMP #oper     C9    2     2
     zeropage      CMP oper      C5    2     3
     zeropage,X    CMP oper,X    D5    2     4
     absolute      CMP oper      CD    3     4
     absolute,X    CMP oper,X    DD    3     4*
     absolute,Y    CMP oper,Y    D9    3     4*
     (indirect,X)  CMP (oper,X)  C1    2     6
     (indirect),Y  CMP (oper),Y  D1    2     5*
*/
void CPU::Core6502::CMP ()
{
    // Z,C,N = A-M
    // This instruction compares the contents of the accumulator with another memory held value 
    // and sets the zero and carry flags as appropriate.

	ARGUMENT = (uint16_t) ACCUMULATOR - ARGUMENT;

	SetCarryFlag   (ACCUMULATOR >= ARGUMENT);
	SetZeroFlag    ((ARGUMENT & 0x00FF) == 0x0000);
	SetNegativeFlag( ARGUMENT & (1 << 7));

    CLOCK++;
}

/**
CPX  Compare Memory and Index X
     X - M                            N Z C I D V
                                      + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     CPX #oper     E0    2     2
     zeropage      CPX oper      E4    2     3
     absolute      CPX oper      EC    3     4
*/
void CPU::Core6502::CPX ()
{
	uint16_t res = (uint16_t) X - ARGUMENT;
    printf("\n%04x - %04x = %04x \n", X, ARGUMENT, res);
	SetCarryFlag   (X >= res);
	SetZeroFlag    ((res & 0x00FF) == 0x0000);
	SetNegativeFlag( res & (1 << 7));
}

/**
CPY  Compare Memory and Index Y
     Y - M                            N Z C I D V
                                      + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     CPY #oper     C0    2     2
     zeropage      CPY oper      C4    2     3
     absolute      CPY oper      CC    3     4
*/
void CPU::Core6502::CPY ()
{
	uint16_t res = (uint16_t) Y - ARGUMENT;

	SetCarryFlag   (Y >= res);
	SetZeroFlag    ((res & 0x00FF) == 0x0000);
	SetNegativeFlag( res & (1 << 7));
}

/**
DEC  Decrement Memory by One
     M - 1 -> M                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      DEC oper      C6    2     5
     zeropage,X    DEC oper,X    D6    2     6
     absolute      DEC oper      CE    3     6
     absolute,X    DEC oper,X    DE    3     7
*/
void CPU::Core6502::DEC ()
{
    // Subtracts one from the value held at a specified memory location 
    // setting the zero and negative flags as appropriate.

    // operand is an address here
    // M, Z, N = M - 1
	uint16_t res = ARGUMENT - 1;
	write(BEF_READING, res & 0x00FF);

	SetZeroFlag    ((res & 0x00FF) == 0x0000);
	SetNegativeFlag( res & (1 << 7) );
}

/**
DEX  Decrement Index X by One
     X - 1 -> X                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       DEC           CA    1     2
*/
void CPU::Core6502::DEX ()
{
    // X,Z,N = X-1
    // Subtracts one from the X register setting the zero and negative flags as appropriate.
    X--;
	SetZeroFlag    ((X & 0x00FF) == 0x0000);
	SetNegativeFlag( X & (1 << 7) );
}

/**
DEY  Decrement Index Y by One
     Y - 1 -> Y                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       DEC           88    1     2
*/
void CPU::Core6502::DEY ()
{
    // X,Z,N = Y-1
    // Subtracts one from the Y register setting the zero and negative flags as appropriate.
    Y--;
	SetZeroFlag    ((Y & 0x00FF) == 0x0000);
	SetNegativeFlag( Y & (1 << 7) );
}

/**
EOR  Exclusive-OR Memory with Accumulator
     A EOR M -> A                     N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     EOR #oper     49    2     2
     zeropage      EOR oper      45    2     3
     zeropage,X    EOR oper,X    55    2     4
     absolute      EOR oper      4D    3     4
     absolute,X    EOR oper,X    5D    3     4*
     absolute,Y    EOR oper,Y    59    3     4*
     (indirect,X)  EOR (oper,X)  41    2     6
     (indirect),Y  EOR (oper),Y  51    2     5*
*/
void CPU::Core6502::EOR ()
{
    // A,Z,N = A^M
    // An exclusive OR is performed, bit by bit, 
    // on the accumulator contents using the contents of a byte of memory.
    ACCUMULATOR ^= ARGUMENT;
	SetZeroFlag    ( (ACCUMULATOR & 0x00FF) == 0x0000);
	SetNegativeFlag( ACCUMULATOR & (1 << 7) );  

    CLOCK++;
}

/**
INC  Increment Memory by One
     M + 1 -> M                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      INC oper      E6    2     5
     zeropage,X    INC oper,X    F6    2     6
     absolute      INC oper      EE    3     6
     absolute,X    INC oper,X    FE    3     7
*/
void CPU::Core6502::INC ()
{
    // M,Z,N = M+1
    // INC - Increment Memory
    ARGUMENT++;
	SetZeroFlag    ( (ARGUMENT & 0x00FF) == 0x0000);
	SetNegativeFlag( ARGUMENT & (1 << 7) );   

    write(BEF_READING, ARGUMENT);
}

/**
INX  Increment Index X by One
     X + 1 -> X                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       INX           E8    1     2
*/
void CPU::Core6502::INX ()
{
    X++;
	SetZeroFlag    ((X & 0x00FF) == 0x0000);
	SetNegativeFlag( X & (1 << 7) );  
}

/**
INY  Increment Index Y by One
     Y + 1 -> Y                       N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       INY           C8    1     2
*/
void CPU::Core6502::INY ()
{
    Y++;
	SetZeroFlag    ((Y & 0x00FF) == 0x0000);
	SetNegativeFlag( Y & (1 << 7) );  
}

/**
JMP  Jump to New Location
     (PC+1) -> PCL                    N Z C I D V
     (PC+2) -> PCH                    - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     absolute      JMP oper      4C    3     3
     indirect      JMP (oper)    6C    3     5
*/
void CPU::Core6502::JMP ()
{
    // Sets the program counter to the address specified by the operand.
    PROG_COUNTER = BEF_READING;
}

/**
JSR  Jump to New Location Saving Return Address
     push (PC+2),                     N Z C I D V
     (PC+1) -> PCL                    - - - - - -
     (PC+2) -> PCH
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     absolute      JSR oper      20    3     6
*/
void CPU::Core6502::JSR ()
{
    // The JSR instruction pushes the address (minus one) of the return point on to the stack 
    // and then sets the program counter to the target memory address.

	PROG_COUNTER--; // return point mem address
    uint8_t pc_HH = (uint8_t) PROG_COUNTER >> 8;
    uint8_t pc_LL = (uint8_t) PROG_COUNTER;

	write(0x0100 + STACK_PTR--, pc_HH);

	write(0x0100 + STACK_PTR--, pc_LL);

	PROG_COUNTER = BEF_READING;
}

/**
LDA  Load Accumulator with Memory
     M -> A                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     LDA #oper     A9    2     2
     zeropage      LDA oper      A5    2     3
     zeropage,X    LDA oper,X    B5    2     4
     absolute      LDA oper      AD    3     4
     absolute,X    LDA oper,X    BD    3     4*
     absolute,Y    LDA oper,Y    B9    3     4*
     (indirect,X)  LDA (oper,X)  A1    2     6
     (indirect),Y  LDA (oper),Y  B1    2     5*
*/
void CPU::Core6502::LDA ()
{
    ACCUMULATOR = ARGUMENT;
    CLOCK++;
}

/**
LDX  Load Index X with Memory
     M -> X                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     LDX #oper     A2    2     2
     zeropage      LDX oper      A6    2     3
     zeropage,Y    LDX oper,Y    B6    2     4
     absolute      LDX oper      AE    3     4
     absolute,Y    LDX oper,Y    BE    3     4*
*/
void CPU::Core6502::LDX ()
{
    X = ARGUMENT;
    CLOCK++;
}

/**
LDY  Load Index Y with Memory
     M -> Y                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     LDY #oper     A0    2     2
     zeropage      LDY oper      A4    2     3
     zeropage,X    LDY oper,X    B4    2     4
     absolute      LDY oper      AC    3     4
     absolute,X    LDY oper,X    BC    3     4*
*/
void CPU::Core6502::LDY ()
{
    Y = ARGUMENT;
    CLOCK++;
}

/**
LSR  Shift One Bit Right (Memory or Accumulator)
     0 -> [76543210] -> C             N Z C I D V
                                      0 + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     accumulator   LSR A         4A    1     2
     zeropage      LSR oper      46    2     5
     zeropage,X    LSR oper,X    56    2     6
     absolute      LSR oper      4E    3     6
     absolute,X    LSR oper,X    5E    3     7
*/
void CPU::Core6502::LSR ()
{
    // A,C,Z,N = A >> 1 or M,C,Z,N = M >> 1
    // Each of the bits in A or M is shift one place to the right. 
    // The bit that was in bit 0 is shifted into the carry flag.
    // Bit 7 is set to zero.

    // [Note] : if Mode acc then ARGUMENT will contain the value of the Accumulator
    // Else it's an address
	SetCarryFlag(ARGUMENT & 1); //  The bit that was in bit 0 is shifted into the carry flag.

	ARGUMENT >>= 1;	
	
	SetZeroFlag    ( (ARGUMENT & 0x00FF) == 0x0000);
	SetNegativeFlag(  ARGUMENT & (1 << 7) ); 

    if ( CURRENT_ADDRMODE == &MODE_ACC ) ACCUMULATOR = ARGUMENT;
    else                                 write(BEF_READING, ARGUMENT);
}

/**
NOP  No Operation
     ---                              N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       NOP           EA    1     2
*/
void CPU::Core6502::NOP ()
{
    if ( CUR_OPCODE == 0xfc ) CLOCK++;
}

/**
ORA  OR Memory with Accumulator
     A OR M -> A                      N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     ORA #oper     09    2     2
     zeropage      ORA oper      05    2     3
     zeropage,X    ORA oper,X    15    2     4
     absolute      ORA oper      0D    3     4
     absolute,X    ORA oper,X    1D    3     4*
     absolute,Y    ORA oper,Y    19    3     4*
     (indirect,X)  ORA (oper,X)  01    2     6
     (indirect),Y  ORA (oper),Y  11    2     5*
*/
void CPU::Core6502::ORA ()
{
    // A,Z,N = A|M
    // An inclusive OR is performed, bit by bit, on the accumulator contents 
    // using the contents of a byte of memory.
    ACCUMULATOR |= ARGUMENT;
	SetZeroFlag    ( (ACCUMULATOR & 0x00FF) == 0x0000);
	SetNegativeFlag(  ACCUMULATOR & (1 << 7) ); 
    CLOCK++;
}

/**
PHA  Push Accumulator on Stack
     push A                           N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       PHA           48    1     3
*/
void CPU::Core6502::PHA ()
{
    // Pushes a copy of the accumulator on to the stack.
    write(0x0100 + STACK_PTR--, ACCUMULATOR);
}

/**
PHP  Push Processor Status on Stack
     push SR                          N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       PHP           08    1     3
*/
void CPU::Core6502::PHP ()
{
    // Pushes a copy of the status flags on to the stack.
    // SetBreakFlag(1);
    write(0x0100 + STACK_PTR--, GetStatusFlag ());
    // SetBreakFlag(0);
}

/**
PLA  Pull Accumulator from Stack
     pull A                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       PLA           68    1     4
*/
void CPU::Core6502::PLA ()
{
    // Pulls an 8 bit value from the stack and into the accumulator. 
    // The zero and negative flags are set as appropriate.    
    ACCUMULATOR = read(++STACK_PTR + 0x0100);
	SetZeroFlag    ( (ACCUMULATOR & 0x00FF) == 0x0000);
	SetNegativeFlag(  ACCUMULATOR & (1 << 7) ); 
}

/**
PLP  Pull Processor Status from Stack
     pull SR                          N Z C I D V
                                      from stack
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       PLP           28    1     4
*/
void CPU::Core6502::PLP ()
{
    // Pulls an 8 bit value from the stack and into the accumulator. 
    // The zero and negative flags are set as appropriate.    
    uint8_t new_state =  read(++STACK_PTR + 0x0100);
    STATUS_FLAG = new_state;
}

/**
ROL  Rotate One Bit Left (Memory or Accumulator)
     C <- [76543210] <- C             N Z C I D V
                                      + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     accumulator   ROL A         2A    1     2
     zeropage      ROL oper      26    2     5
     zeropage,X    ROL oper,X    36    2     6
     absolute      ROL oper      2E    3     6
     absolute,X    ROL oper,X    3E    3     7
*/
void CPU::Core6502::ROL ()
{
    // Move each of the bits in either A or M one place to the left. 
    // Bit 0 is filled with the current value of the carry flag whilst 
    // the old bit 7 becomes the new carry flag value.
	uint16_t res = (ARGUMENT << 1) | GetCarryFlag();

	SetCarryFlag   (res & 0xFF00);
	SetZeroFlag    ((res & 0x00FF) == 0x0000);
	SetNegativeFlag(res & 0x0080);

	if (CURRENT_ADDRMODE == &MODE_IMP) ACCUMULATOR = res;
	else                               write(BEF_READING, res);
}

/**
ROR  Rotate One Bit Right (Memory or Accumulator)
     C -> [76543210] -> C             N Z C I D V
                                      + + + - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     accumulator   ROR A         6A    1     2
     zeropage      ROR oper      66    2     5
     zeropage,X    ROR oper,X    76    2     6
     absolute      ROR oper      6E    3     6
     absolute,X    ROR oper,X    7E    3     7
*/
void CPU::Core6502::ROR ()
{
    // Move each of the bits in either A or M one place to the right. 
    // Bit 7 is filled with the current value of the carry flag whilst 
    // the old bit 0 becomes the new carry flag value.
    uint16_t res = GetCarryFlag ();
	         res = (res << 7) | (ARGUMENT >> 1);

	SetCarryFlag   (ARGUMENT & 1); //  the old bit 0 becomes the new carry flag value.
	SetZeroFlag    ((res & 0x00FF) == 0x0000);
	SetNegativeFlag( res & 0x0080);

	if (CURRENT_ADDRMODE == &MODE_IMP) ACCUMULATOR = res;
	else                               write(BEF_READING, res);
}

/**
RTI  Return from Interrupt
     pull SR, pull PC                 N Z C I D V
                                      from stack
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       RTI           40    1     6
*/
void CPU::Core6502::RTI ()
{
    // The RTI instruction is used at the end of an interrupt processing routine. 
    // It pulls the processor flags from the stack followed by the program counter.
    STATUS_FLAG  = read(++STACK_PTR + 0x0100);

    uint16_t LL  = read(++STACK_PTR + 0x0100); 
    uint16_t HH  = read(++STACK_PTR + 0x0100); 
    PROG_COUNTER = (HH << 8) | LL;
}

/**
RTS  Return from Subroutine
     pull PC, PC+1 -> PC              N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       RTS           60    1     6
*/
void CPU::Core6502::RTS ()
{
    // The RTS instruction is used at the end of a subroutine to return to the calling routine. 
    // It pulls the program counter (minus one) from the stack.
    uint16_t LL = read(++STACK_PTR + 0x0100);
    uint16_t HH = read(++STACK_PTR + 0x0100);
    PROG_COUNTER = (HH << 8) | LL;
}

/**
SBC  Subtract Memory from Accumulator with Borrow
     A - M - C -> A                   N Z C I D V
                                      + + + - - +
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     immidiate     SBC #oper     E9    2     2
     zeropage      SBC oper      E5    2     3
     zeropage,X    SBC oper,X    F5    2     4
     absolute      SBC oper      ED    3     4
     absolute,X    SBC oper,X    FD    3     4*
     absolute,Y    SBC oper,Y    F9    3     4*
     (indirect,X)  SBC (oper,X)  E1    2     6
     (indirect),Y  SBC (oper),Y  F1    2     5*
*/
void CPU::Core6502::SBC ()
{
    uint16_t operand = ARGUMENT;
    uint16_t value = operand ^ 0x00FF;

    uint16_t a = ACCUMULATOR;
    uint16_t op = value;
    uint16_t c = GetCarryFlag();
    
	uint16_t sum = a + op + c;
	SetCarryFlag    (sum & 0xFF00);
	SetZeroFlag     ((sum & 0x00FF) == 0);
	SetOverFlowFlag ((sum ^ a) & (sum ^ op) & 0x0080);
	SetNegativeFlag (sum & 0x0080);

	ACCUMULATOR = sum & 0x00FF;

    CLOCK++;
}

/**
SEC  Set Carry Flag
     1 -> C                           N Z C I D V
                                      - - 1 - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       SEC           38    1     2
*/
void CPU::Core6502::SEC ()
{
    SetCarryFlag (1);
}

/**
SED  Set Decimal Flag
     1 -> D                           N Z C I D V
                                      - - - - 1 -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       SED           F8    1     2
*/
void CPU::Core6502::SED ()
{
    SetDecimalModeFlag (1);
}

/**
SEI  Set Interrupt Disable Status
     1 -> I                           N Z C I D V
                                      - - - 1 - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       SEI           78    1     2
*/
void CPU::Core6502::SEI ()
{
    SetIRQFlag (1);
}

/**
STA  Store Accumulator in Memory
     A -> M                           N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      STA oper      85    2     3
     zeropage,X    STA oper,X    95    2     4
     absolute      STA oper      8D    3     4
     absolute,X    STA oper,X    9D    3     5
     absolute,Y    STA oper,Y    99    3     5
     (indirect,X)  STA (oper,X)  81    2     6
     (indirect),Y  STA (oper),Y  91    2     6
*/
void CPU::Core6502::STA ()
{
    // M = A
    // Stores the contents of the accumulator into memory.
    write (BEF_READING, ACCUMULATOR);
}

/**
STX  Store Index X in Memory
     X -> M                           N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      STX oper      86    2     3
     zeropage,Y    STX oper,Y    96    2     4
     absolute      STX oper      8E    3     4
*/
void CPU::Core6502::STX ()
{
    // M = X
    // Stores the contents of the X register into memory.
    write (BEF_READING, X);
}

/**
STY  Sore Index Y in Memory
     Y -> M                           N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     zeropage      STY oper      84    2     3
     zeropage,X    STY oper,X    94    2     4
     absolute      STY oper      8C    3     4
*/
void CPU::Core6502::STY ()
{
    // M = Y
    // Stores the contents of the Y register into memory.
    write (BEF_READING, Y);
}

/**
TAX  Transfer Accumulator to Index X
     A -> X                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TAX           AA    1     2
*/
void CPU::Core6502::TAX ()
{
    // X = A
    X = ACCUMULATOR;
}

/**
TAY  Transfer Accumulator to Index Y
     A -> Y                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TAY           A8    1     2
*/
void CPU::Core6502::TAY ()
{
    // Y = A
    Y = ACCUMULATOR;
}

/**
TSX  Transfer Stack Pointer to Index X
     SP -> X                          N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TSX           BA    1     2
*/
void CPU::Core6502::TSX ()
{
    // X = S
    // Copies the current contents of the stack register into the X register 
    // and sets the zero and negative flags as appropriate.
    X = STACK_PTR;
	SetZeroFlag     ( (X & 0x00FF) == 0x0000);
	SetNegativeFlag (  X & (1 << 7) );  
}

/**
TXA  Transfer Index X to Accumulator
     X -> A                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TXA           8A    1     2
*/
void CPU::Core6502::TXA ()
{
    // A = X
    // Copies the current contents of the X register into the accumulator and sets the zero and negative flags as appropriate.
    ACCUMULATOR = X;
	SetZeroFlag     ( (ACCUMULATOR & 0x00FF) == 0x0000);
	SetNegativeFlag (  ACCUMULATOR & (1 << 7) );  
}

/**
TXS  Transfer Index X to Stack Register
     X -> SP                          N Z C I D V
                                      - - - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TXS           9A    1     2
*/
void CPU::Core6502::TXS ()
{
    // S = X
    // Copies the current contents of the X register into the stack register.
    STACK_PTR = X;
}

/**
TYA  Transfer Index Y to Accumulator
     Y -> A                           N Z C I D V
                                      + + - - - -
     addressing    assembler    opc  bytes  cyles
     --------------------------------------------
     implied       TYA           98    1     2
  *  add 1 to cycles if page boundery is crossed
  ** add 1 to cycles if branch occurs on same page
     add 2 to cycles if branch occurs to different page
     Legend to Flags:  + .... modified
                       - .... not modified
                       1 .... set
                       0 .... cleared
                      M6 .... memory bit 6
                      M7 .... memory bit 7
*/
void CPU::Core6502::TYA ()
{
    // A = Y
    // Copies the current contents of the Y register into the accumulator 
    // and sets the zero and negative flags as appropriate.
    ACCUMULATOR = Y;
	SetZeroFlag     ( (ACCUMULATOR & 0x00FF) == 0x0000);
	SetNegativeFlag (  ACCUMULATOR & (1 << 7) );  
}