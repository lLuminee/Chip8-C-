#include "../include/cpu.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iomanip>

void CPU::LoadFontset(uint8_t *memory) {
    uint8_t fontset[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    for (int i = 0; i < 80; i++) {
        memory[i] = fontset[i];
    }
}


CPU::CPU() 
{
    std::cout << "CPU Constructor" << std::endl;
    pc = 0x200;
    memset(memory, 0, sizeof(memory));
    memset(registre, 0, 16);
    I = 0;
    opcode = 0;
    pile.resize(16);
    memset(pile.data(), 0, sizeof(pile));
    LoadFontset(memory);
    
}


void CPU::loadGame() {
    std::cout << "File Contents:" << std::endl;

    FILE *file = fopen("rom/breakout.rom", "r");
    if (file == NULL) {
        std::cout << "Error: Couldn't open the file" << std::endl;
        exit(1);
    } else {
        fread(&memory[0x200], 0xfff, 1, file);
        fclose(file);
    }
    std::cout << "Game Loaded" << std::endl;
}



void CPU::PrintAllMemory() {
    std::cout << std::endl;
    std::cout << "Printing Memory in Hex" << std::endl;

    for (int i = 0; i < 0xFFF; i++) {
        std::cout << toHexString(memory[i]) << " ";
    }

    std::cout << std::endl;
    std::cout << "Print Memory in int" << std::endl;

    for (int i = 0; i < 0xFFF; i++) {
        std::cout << std::to_string(memory[i]) << " ";
    }
    std::cout << std::endl;
    std::cout << "Print Memory Success" << std::endl;
}

std::string CPU::toHexString(uint8_t value) {
    std::ostringstream oss;
    oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
    return oss.str();
}

std::string CPU::toHexString(uint16_t value) {
    std::ostringstream oss;
    oss << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(value);
    return oss.str();
}


void CPU::PrintOpocdeMemory() {
    std::cout << "Printing Opcodes" << std::endl;

    for (int i = 0; i < 0xFFF; i += 2) {
        if (memory[i] != 0 || memory[i + 1] != 0) {
            std::cout << toHexString(memory[i]) << toHexString(memory[i + 1]) << " at address: " << i << std::endl;
        }
    }

    std::cout << std::endl;
}
