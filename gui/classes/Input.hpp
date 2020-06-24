#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

class Input {
public:
    enum INPUT_FLAGS {
        UP    = (1 << 7),
        DOWN  = (1 << 6),
        LEFT  = (1 << 5),
        RIGHT = (1 << 4),
        SPACE = (1 << 3)
    };

    Input(uint16_t input_addr) {
        this->input_addr = input_addr;
    }
    virtual ~Input();

    uint8_t readMemory(std::map<uint16_t, uint8_t>* ram) {
        return (*ram)[input_addr];
    }

    void SetInputMemory(INPUT_FLAGS in, bool value, std::map<uint16_t, uint8_t>* ram) {
        uint8_t INPUT_STATUS = readMemory( ram );
        if ( value ) {
            //INPUT_STATUS |=  in;
        } else {
            //INPUT_STATUS &= ~in;
        }
        (*ram)[input_addr] = INPUT_STATUS;
    }

    bool GetInput(INPUT_FLAGS in, std::map<uint16_t, uint8_t>* ram) {
        uint8_t INPUT_STATUS = readMemory( ram );
        return (bool) 1;// (INPUT_STATUS & in);
    }

private:
    uint16_t input_addr = 0x05FF;
};
