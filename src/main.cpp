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
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); 

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
        
if (IsKeyDown(KEY_KP_7)) cpu.touche[0x0] = true; else cpu.touche[0x0] = false;
if (IsKeyDown(KEY_KP_8)) cpu.touche[0x1] = true; else cpu.touche[0x1] = false;
if (IsKeyDown(KEY_KP_9)) cpu.touche[0x2] = true; else cpu.touche[0x2] = false; 
if (IsKeyDown(KEY_KP_MULTIPLY)) cpu.touche[0x3] = true; else cpu.touche[0x3] = false;
if (IsKeyDown(KEY_KP_4)) cpu.touche[0x4] = true; else cpu.touche[0x4] = false; 
if (IsKeyDown(KEY_KP_5)) cpu.touche[0x5] = true; else cpu.touche[0x5] = false; 
if (IsKeyDown(KEY_KP_6)) cpu.touche[0x6] = true; else cpu.touche[0x6] = false;
if (IsKeyDown(KEY_KP_SUBTRACT)) cpu.touche[0x7] = true; else cpu.touche[0x7] = false;
if (IsKeyDown(KEY_KP_1)) cpu.touche[0x8] = true; else cpu.touche[0x8] = false;
if (IsKeyDown(KEY_KP_2)) cpu.touche[0x9] = true; else cpu.touche[0x9] = false; 
if (IsKeyDown(KEY_KP_3)) cpu.touche[0xA] = true; else cpu.touche[0xA] = false;
if (IsKeyDown(KEY_KP_ADD)) cpu.touche[0xB] = true; else cpu.touche[0xB] = false;
if (IsKeyDown(KEY_RIGHT)) cpu.touche[0xC] = true; else cpu.touche[0xC] = false;
if (IsKeyDown(KEY_KP_0)) cpu.touche[0xD] = true; else cpu.touche[0xD] = false;
if (IsKeyDown(KEY_PERIOD)) cpu.touche[0xE] = true; else cpu.touche[0xE] = false; 
if (IsKeyDown(KEY_KP_ENTER)) cpu.touche[0xF] = true; else cpu.touche[0xF] = false;

// Gérer la touche d'échappement séparément
if (IsKeyDown(KEY_ESCAPE)) exit(0);
    

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

    // - Delay Timer en hexadécimal
    DrawText("Delay Timer: ", 0, 600, 20, WHITE);
    DrawText(cpu.toHexString(cpu.delay_timer).c_str(), 130, 600, 20, WHITE);

    // - Registres en hexadécimal
    DrawText("V0:",850, 20, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[1]).c_str(), 890, 20, 20, WHITE);
    DrawText("V1:",850, 50, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[2]).c_str(), 890, 50, 20, WHITE);
    DrawText("V2:",850, 80, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[3]).c_str(), 890, 80, 20, WHITE);
    DrawText("V3:",850, 110, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[4]).c_str(), 890, 110, 20, WHITE);
    DrawText("V4:",850, 140, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[5]).c_str(), 890, 140, 20, WHITE);
    DrawText("V5:",850, 170, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[6]).c_str(), 890, 170, 20, WHITE);
    DrawText("V6:",850, 200, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[7]).c_str(), 890, 200, 20, WHITE);
    DrawText("V7:",850, 230, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[8]).c_str(), 890, 230, 20, WHITE);
    DrawText("V8:",850, 260, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[9]).c_str(), 890, 260, 20, WHITE);
    DrawText("V9:",850, 290, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[10]).c_str(), 890, 290, 20, WHITE);
    DrawText("VA:",850, 320, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[11]).c_str(), 890, 320, 20, WHITE);
    DrawText("VB:",850, 350, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[12]).c_str(), 890, 350, 20, WHITE);
    DrawText("VV:",850, 380, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[13]).c_str(), 890, 380, 20, WHITE);
    DrawText("VD:",850, 410, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[14]).c_str(), 890, 410, 20, WHITE);
    DrawText("VE:",850, 440, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[15]).c_str(), 890, 440, 20, WHITE);
    DrawText("VF",850, 470, 20 , WHITE); DrawText(cpu.toHexString(cpu.registre[16]).c_str(), 890, 470, 20, WHITE);


    DrawText("Stack 1:", 950, 20, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[0]).c_str(), 1050, 20, 20, WHITE);
    DrawText("Stack 2:", 950, 50, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[1]).c_str(), 1050, 50, 20, WHITE);
    DrawText("Stack 3:", 950, 80, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[2]).c_str(), 1050, 80, 20, WHITE);
    DrawText("Stack 4:", 950, 110, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[3]).c_str(), 1050, 110, 20, WHITE);
    DrawText("Stack 5:", 950, 140, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[4]).c_str(), 1050, 140, 20, WHITE);
    DrawText("Stack 6:", 950, 170, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[5]).c_str(), 1050, 170, 20, WHITE);
    DrawText("Stack 7:", 950, 200, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[6]).c_str(), 1050, 200, 20, WHITE);
    DrawText("Stack 8:", 950, 230, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[7]).c_str(), 1050, 230, 20, WHITE);
    DrawText("Stack 9:", 950, 260, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[8]).c_str(), 1050, 260, 20, WHITE);
    DrawText("Stack 10:", 950, 290, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[9]).c_str(), 1050, 290, 20, WHITE);
    DrawText("Stack 11:", 950, 320, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[10]).c_str(), 1050, 320, 20, WHITE);
    DrawText("Stack 12:", 950, 350, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[11]).c_str(), 1050, 350, 20, WHITE);
    DrawText("Stack 13:", 950, 380, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[12]).c_str(), 1050, 380, 20, WHITE);
    DrawText("Stack 14:", 950, 410, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[13]).c_str(), 1050, 410, 20, WHITE);
    DrawText("Stack 15:", 950, 440, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[14]).c_str(), 1050, 440, 20, WHITE);
    DrawText("Stack 16:", 950, 470, 20, WHITE); DrawText(cpu.toHexString(cpu.pile[15]).c_str(), 1050, 470, 20, WHITE);

    
    DrawText("Touche 1", 180, 430,15, WHITE); DrawText(cpu.touche[0] ? "1" : "0", 180, 450, 15, WHITE);
    DrawText("Touche 2", 250, 430,15, WHITE); DrawText(cpu.touche[1] ? "1" : "0", 250, 450, 15, WHITE);
    DrawText("Touche 3", 320, 430,15, WHITE); DrawText(cpu.touche[2] ? "1" : "0", 320, 450, 15, WHITE);
    DrawText("Touche 4", 390, 430,15, WHITE); DrawText(cpu.touche[3] ? "1" : "0", 390, 450, 15, WHITE);
    DrawText("Touche 5", 460, 430,15, WHITE); DrawText(cpu.touche[4] ? "1" : "0", 460, 450, 15, WHITE);
    DrawText("Touche 6", 530, 430,15, WHITE); DrawText(cpu.touche[5] ? "1" : "0", 530, 450, 15, WHITE);
    DrawText("Touche 7", 600, 430,15, WHITE); DrawText(cpu.touche[6] ? "1" : "0", 600, 450, 15, WHITE);
    DrawText("Touche 8", 670, 430,15, WHITE); DrawText(cpu.touche[7] ? "1" : "0", 670, 450, 15, WHITE);

    DrawText("Touche 9", 180, 500,15, WHITE); DrawText(cpu.touche[8] ? "1" : "0", 180, 520, 15, WHITE);
    DrawText("Touche A", 250, 500,15, WHITE); DrawText(cpu.touche[9] ? "1" : "0", 250, 520, 15, WHITE);
    DrawText("Touche B", 320, 500,15, WHITE); DrawText(cpu.touche[10] ? "1" : "0", 320, 520, 15, WHITE);
    DrawText("Touche C", 390, 500,15, WHITE); DrawText(cpu.touche[11] ? "1" : "0", 390, 520, 15, WHITE);
    DrawText("Touche D", 460, 500,15, WHITE); DrawText(cpu.touche[12] ? "1" : "0", 460, 520, 15, WHITE);
    DrawText("Touche E", 530, 500,15, WHITE); DrawText(cpu.touche[13] ? "1" : "0", 530, 520, 15, WHITE);
    DrawText("Touche F", 600, 500,15, WHITE); DrawText(cpu.touche[14] ? "1" : "0", 600, 520, 15, WHITE);
    DrawText("Touche 0", 670, 500,15, WHITE); DrawText(cpu.touche[15] ? "1" : "0", 670, 520, 15, WHITE);

        grid.print();  
        EndDrawing();
    }

    

    return 0;
    
}
