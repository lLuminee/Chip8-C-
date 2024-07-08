#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "raylib.h"
#include "../include/grid.h"
#include "../include/cpu.h"	
#include "../include/opcode.h"
#include <thread>
#include <chrono>


#define height 1920 / 1.5 
#define width 1080 /  1.5

int main() {

    InitWindow(height,width, "Chip8");
    std::cout << "Starting Emulator" << std::endl;
    Grid grid = Grid();
    CPU cpu = CPU();
    opcode op;

    cpu.loadGame();
    cpu.PrintAllMemory();
    cpu.PrintOpocdeMemory();

    op.initializeOpcodeMask();
    
    grid.initialize();



    while (!WindowShouldClose())
    {
        BeginDrawing();

        // Delay for 16 milliseconds
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 

        ClearBackground(BLACK);

        if (cpu.pc >= 0xFFF) {
            std::cout << "Error: PC out of memory" << std::endl;
            return 1;
        }
        else{

            for  (int i = 0; i < 3; i++) {
                cpu.opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];
                std::cout << "PC: " << std::to_string(cpu.pc) << std::endl;
                std::cout << "Opcode: " << std::hex << cpu.opcode << std::endl;

                op.DecodOpcode(&cpu, cpu.opcode, &grid);
                std::cout << std::endl;
            }

        }
    
    // Print Information

    // - OPCODE en hexadécimal
    DrawText("Opcode: ", 0, 450, 20, WHITE);
    DrawText(cpu.toHexString(static_cast<uint16_t>(cpu.opcode)).c_str(), 80, 450, 20, WHITE);
    
    // - PC en hexadécimal
    DrawText("PC: ", 0, 500, 20, WHITE);
    DrawText(cpu.toHexString(cpu.pc).c_str(), 40, 500, 20, WHITE);

    // - I en hexadécimal
    DrawText("I: ", 0, 550, 20, WHITE);
    DrawText(cpu.toHexString(cpu.I).c_str(), 20, 550, 20, WHITE);


        grid.print();  
        EndDrawing();
    }

    

    return 0;
    
}
