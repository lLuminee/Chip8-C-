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
    std::string string_opcode;
    uint16_t opcode;
    uint16_t Befor_opcode;
    uint16_t After_opcode;
    uint8_t touche[16];
    const char* GameName;

    
    void initialize();
    void loadGame(const char* GameName);
    void LoadFontset(uint8_t *memory);
    std::string PrintOpocdeMemory();
    void PrintAllMemory();
    std::string toHexString(uint8_t value);
    std::string toHexString(uint16_t value);


    CPU();

};