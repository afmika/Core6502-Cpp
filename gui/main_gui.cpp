#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "../component/cpu.h"

#include "./classes/Pixel.hpp"
#include "./classes/Monitor.hpp"
#include "./classes/Input.hpp"

const uint32_t fps = 16;
const uint32_t screen_dim = 600;
const uint32_t n_tiles  = 30;
const uint32_t dim_pixel  = screen_dim / n_tiles;
sf::Font font;


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

int main() {
    sf::RenderWindow window(sf::VideoMode(screen_dim, screen_dim), "Monitor");
    window.setFramerateLimit( fps );
    std::string font_path = "./font/ibm.ttf";
    if(!font.loadFromFile(font_path)) { printf("Error loading %s\n", font_path.c_str() );}

    // monitor
    Monitor* monitor = new Monitor ( &window, dim_pixel );
    // input
    //Input* input_manager = new Input (0x05FF);

    // initializing the cpu
    CPU::BUS* bus = new CPU::BUS(0x0000, 0xFFFF, false);
    CPU::Core6502* cpu = new CPU::Core6502();
    cpu->Connect( bus );
    bus->loadProgram("A9 04 8D 00 06 A9 05 8D 01 06 A9 FF 8D 02 06 AE 02 06 E8 8E 02 06");

    // main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // displaying
        cpu->Next(); // next instruction
        monitor->readMemory( &bus->MEMORY ); // read(0x0600 to 0x0600 + tot_size)
        // input_manager->readMemory( &bus->MEMORY );

        debug_info(cpu, &window);

        window.display();
        window.clear(sf::Color::Black);
    }
    return 0;
}
