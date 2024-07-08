#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

class CPU {

public:
    // Variables membres
    uint8_t memory[0xFFF];
    uint8_t registre[16];
    std::vector<uint16_t> pile;
    uint16_t delay_timer;
    uint16_t sound_timer;
    uint16_t I;
    uint16_t pc;
    uint16_t opcode;
    

    void loadGame();
    void LoadFontset(uint8_t *memory);
    void PrintOpocdeMemory();
    void PrintAllMemory();
    std::string toHexString(uint8_t value);
    std::string toHexString(uint16_t value);


    CPU();

};