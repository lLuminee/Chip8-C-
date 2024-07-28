#pragma once
#include <string>
#include "../include/cpu.h"
#include "../include/grid.h"
#include "../include/opcode.h"

class Chip8
{
public:
    void Emulation(int argc, char** argv, bool already_game, const char*game_name, bool Step_par_Step);

private:

};

