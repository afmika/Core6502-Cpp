#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "../component/cpu.h"

const uint32_t fps = 24;
const uint32_t screen_dim = 600;
const uint32_t tiles_dim  = 25;
const uint32_t dim_pixel  = screen_dim / tiles_dim;
sf::Font font;

// helpers
uint16_t Convert16BitToRGB (uint8_t color_8bit ) {
    // personal taste. don't judge me
    // 8 bits : R|G|B|B : 2 bits each
    // 8 bits : [RR][GG][BB][BB] : blue is life
    uint16_t r = (color_8bit & 0b11000000) >> 6,
             g = (color_8bit & 0b00110000) >> 4,
             b = (color_8bit & 0b00001111) >> 0;
    return (r << 12) | (g << 8) | b;
}
// debug_info
void debug_info(CPU::Core6502* cpu, sf::RenderWindow* window) {
    uint8_t X      = cpu->GetXRegister     (),
            Y      = cpu->GetYRegister     (),
            A      = cpu->GetARegister     (),
            PC     = cpu->GetProgCounter   (),
            SP     = cpu->GetStackPtrvalue (),
            STATUS = cpu->GetStatusFlag    ();
    // aaah..
    sf::Vector2f anchor(10, 10);

    char text[200];
    sprintf(text, "X=%02x Y=%02x A=%02x | PC $%04x | STATUS %02x | STK %02x", X, Y, A, PC, STATUS, SP);
    // std::string info((const char*) text);
    std::string info(text);
    sf::Text disp_text;
    disp_text.setFont      ( font );
    disp_text.setPosition  (anchor);
    disp_text.setString    ( info );
    disp_text.setFillColor (sf::Color::White);

    disp_text.setCharacterSize(20);
    window->draw(disp_text);
}

// this struct will be used inside the monitor
typedef struct Pixel {
    uint8_t x;
    uint8_t y;
    uint8_t color;
    Pixel (int x, int y) : x(x), y(y) {
        color = 0xFF; // white
    }
    Pixel() : x(), y() {
        color = 0xFF; // white
    }

    void put(sf::RenderWindow& window) {
        uint16_t rgb = Convert16BitToRGB( color );
        uint8_t r = (rgb & 0xFF0000) >> 12,
                g = (rgb & 0x00FF00) >>  8,
                b = (rgb & 0x0000FF) >>  0;
        sf::Color color(r, g, b);

        sf::RectangleShape rect;
        rect.setPosition(sf::Vector2f(tiles_dim * x, tiles_dim * y));
        rect.setFillColor(color);
        rect.setSize(sf::Vector2f(dim_pixel, dim_pixel));

        window.draw( rect );
    }
} Pixel;

// monitor : can display 16 x 16 tiles
// 1 pixel => (1byteX, 1byteY, 1 byte of color)
// this device reads from 0x0600 to 0x0600 + 3 * (n_pixels) % 0xffff
typedef struct Monitor {
    sf::RenderWindow* window = nullptr;
    Monitor (sf::RenderWindow* window) { this->window = window; }

    void readMemory(std::map<uint16_t, uint8_t>* ram) {
        // position info
        int n_pixel     = 32; // w x h
        int infos_count = 3; // 3 bytes (x, y, 8bitcolor)
        uint16_t rmin = 0x0600;
        uint16_t rmax = rmin + infos_count * (n_pixel * n_pixel);

        uint16_t ptr = rmin;
        while ( ptr <= rmax ) {
            // [Note] possible range for x, y, color = $00 to $ff
            uint8_t x     = (*ram)[ ptr++ ];
            uint8_t y     = (*ram)[ ptr++ ];
            uint8_t color = (*ram)[ ptr++ ];
            // if ( x != 0 || y != 0 || color != 0) printf("%02x %02x %02x\n", x, y, color);
            Pixel pixel(x, y);
            pixel.color = color;
            pixel.put( *window );
        }
    }
} Monitor;

typedef struct Input {

} Input;

int main() {
    sf::RenderWindow window(sf::VideoMode(screen_dim, screen_dim), "Monitor");
    window.setFramerateLimit( fps );
    std::string font_path = "./font/ibm.ttf";
    if(!font.loadFromFile(font_path)) { printf("Error loading %s\n", font_path.c_str() );}
    // Pixel pixel = {3, 4};

    // monitor
    Monitor* monitor = new Monitor ( &window );

    // initializing the cpu
    CPU::BUS* bus = new CPU::BUS(0x0000, 0xffff, false);
    CPU::Core6502* cpu = new CPU::Core6502();
    cpu->Connect( bus );
    // bus->loadProgram("A9 04 8D 00 06 A9 05 8D 01 06 A9 FF 8D 02 06");
    bus->loadProgram("A9 04 8D 00 06 A9 05 8D 01 06 A9 FF 8D 02 06 AE 02 06 E8 8E 02 06");

    // main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // displaying
        cpu->Next();
        monitor->readMemory( &bus->MEMORY );

        debug_info(cpu, &window);

        // pixel.put( window );
        window.display();
        window.clear(sf::Color::Black);
    }
    return 0;
}
