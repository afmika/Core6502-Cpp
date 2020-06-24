#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#include "./Pixel.hpp"

// monitor : can display 16 x 16 tiles
// 1 pixel => (1byteX, 1byteY, 1 byte of color)
// this device reads from 0x0600 to 0x0600 + 3 * (n_pixels) % 0xffff
class Monitor {
public:
    sf::RenderWindow* window = nullptr;
    uint32_t dim_pixel = 10;
    Monitor (sf::RenderWindow* window, uint32_t dim_pixel) {
        this->window = window;
        this->dim_pixel = dim_pixel;
    }

    void readMemory(std::map<uint16_t, uint8_t>* ram) {
        // position info
        int n_pixel     = 32; // w x h
        int infos_count = 3; // 3 bytes (x, y, 8 bits of color)

        uint16_t rmin = 0x0600;
        uint16_t rmax = rmin + infos_count * (n_pixel * n_pixel);

        uint16_t ptr  = rmin;
        while (  ptr <= rmax ) {
            // [Note] possible range for x, y, color = $00 to $ff
            uint8_t x     = (*ram)[ ptr++ ];
            uint8_t y     = (*ram)[ ptr++ ];
            uint8_t color = (*ram)[ ptr++ ];
            // if ( x != 0 || y != 0 || color != 0) printf("%02x %02x %02x\n", x, y, color);
            Pixel pixel(x, y);
            pixel.color = color;
            pixel.put( *window, dim_pixel );
        }
    }
};
