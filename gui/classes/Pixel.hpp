#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>


// helper
uint16_t Convert16BitToRGB (uint8_t color_8bit ) {
    // personal taste. don't judge me
    // 8 bits : R|G|B|B : 2 bits each
    // 8 bits : [RR][GG][BB][BB] : blue is life
    uint16_t r = (color_8bit & 0b11000000) >> 6,
             g = (color_8bit & 0b00110000) >> 4,
             b = (color_8bit & 0b00001111) >> 0;
    return (r << 12) | (g << 8) | b;
}

// this struct will be used inside the monitor
class Pixel {
public:
    uint8_t x;
    uint8_t y;
    uint8_t color;
    Pixel (int x, int y) : x(x), y(y) {
        color = 0xFF; // white
    }
    Pixel() : x(), y() {
        color = 0xFF; // white
    }
    virtual ~Pixel() {}

    void put(sf::RenderWindow& window, uint32_t dim_pixel) {
        uint16_t rgb = Convert16BitToRGB( color );
        uint8_t r = (rgb & 0xFF0000) >> 12,
                g = (rgb & 0x00FF00) >>  8,
                b = (rgb & 0x0000FF) >>  0;
        sf::Color color(r, g, b);

        sf::RectangleShape rect;
        rect.setPosition(sf::Vector2f(dim_pixel * x, dim_pixel * y));
        rect.setFillColor(color);
        rect.setSize(sf::Vector2f(dim_pixel, dim_pixel));

        window.draw( rect );
    }
};
