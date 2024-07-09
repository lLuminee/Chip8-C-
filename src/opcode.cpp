#include "../include/opcode.h"
#include <iostream>
#include "../include/cpu.h"
#include "../include/grid.h"

struct opcodeMask
{
    uint16_t masque[35];
    uint16_t id[35];
};

opcodeMask jp;
void opcode::initializeOpcodeMask()
{
  jp.masque[0]= 0x0000; jp.id[0]=0x0FFF;          /* 0NNN */ 
  jp.masque[1]= 0xFFFF; jp.id[1]=0x00E0;          /* 00E0 */ 
  jp.masque[2]= 0xFFFF; jp.id[2]=0x00EE;          /* 00EE */ 
  jp.masque[3]= 0xF000; jp.id[3]=0x1000;          /* 1NNN */ 
  jp.masque[4]= 0xF000; jp.id[4]=0x2000;          /* 2NNN */ 
  jp.masque[5]= 0xF000; jp.id[5]=0x3000;          /* 3XNN */ 
  jp.masque[6]= 0xF000; jp.id[6]=0x4000;          /* 4XNN */ 
  jp.masque[7]= 0xF00F; jp.id[7]=0x5000;          /* 5XY0 */ 
  jp.masque[8]= 0xF000; jp.id[8]=0x6000;          /* 6XNN */ 
  jp.masque[9]= 0xF000; jp.id[9]=0x7000;          /* 7XNN */ 
  jp.masque[10]= 0xF00F; jp.id[10]=0x8000;          /* 8XY0 */ 
  jp.masque[11]= 0xF00F; jp.id[11]=0x8001;          /* 8XY1 */ 
  jp.masque[12]= 0xF00F; jp.id[12]=0x8002;          /* 8XY2 */ 
  jp.masque[13]= 0xF00F; jp.id[13]=0x8003;          /* 8XY3 */ 
  jp.masque[14]= 0xF00F; jp.id[14]=0x8004;          /* 8XY4 */ 
  jp.masque[15]= 0xF00F; jp.id[15]=0x8005;          /* 8XY5 */ 
  jp.masque[16]= 0xF00F; jp.id[16]=0x8006;          /* 8XY6 */ 
  jp.masque[17]= 0xF00F; jp.id[17]=0x8007;          /* 8XY7 */ 
  jp.masque[18]= 0xF00F; jp.id[18]=0x800E;          /* 8XYE */ 
  jp.masque[19]= 0xF00F; jp.id[19]=0x9000;          /* 9XY0 */ 
  jp.masque[20]= 0xF000; jp.id[20]=0xA000;          /* ANNN */ 
  jp.masque[21]= 0xF000; jp.id[21]=0xB000;          /* BNNN */ 
  jp.masque[22]= 0xF000; jp.id[22]=0xC000;          /* CXNN */ 
  jp.masque[23]= 0xF000; jp.id[23]=0xD000;          /* DXYN */ 
  jp.masque[24]= 0xF0FF; jp.id[24]=0xE09E;          /* EX9E */ 
  jp.masque[25]= 0xF0FF; jp.id[25]=0xE0A1;          /* EXA1 */ 
  jp.masque[26]= 0xF0FF; jp.id[26]=0xF007;          /* FX07 */ 
  jp.masque[27]= 0xF0FF; jp.id[27]=0xF00A;          /* FX0A */ 
  jp.masque[28]= 0xF0FF; jp.id[28]=0xF015;          /* FX15 */ 
  jp.masque[29]= 0xF0FF; jp.id[29]=0xF018;          /* FX18 */ 
  jp.masque[30]= 0xF0FF; jp.id[30]=0xF01E;          /* FX1E */ 
  jp.masque[31]= 0xF0FF; jp.id[31]=0xF029;          /* FX29 */ 
  jp.masque[32]= 0xF0FF; jp.id[32]=0xF033;          /* FX33 */ 
  jp.masque[33]= 0xF0FF; jp.id[33]=0xF055;          /* FX55 */ 
  jp.masque[34]= 0xF0FF; jp.id[34]=0xF065;          /* FX65 */}

uint16_t GetAction(uint16_t opcode, CPU *cpu) {
    uint16_t resultat; 
    for (int i = 0; i < 35; i++) {
        resultat= (jp.masque[i]&opcode);  /* On récupère les bits concernés par le test, l'identifiant de l'opcode */  
        if(resultat == jp.id[i]) {
            return i;
        }
    
    }
    return 0;
}

void opcode::CLS_00E0_OP(CPU *cpu, Grid *grid){
    grid->clearGrid();
    cpu->pc += 2;
}

void opcode::RET_00EE_OP(CPU *cpu){
    cpu->pc += 2;
}

void opcode::SYS_0NNN_OP(CPU *cpu, uint16_t opcode){
    cpu->pc = opcode & 0x0FFF;
}

void opcode::JP_1NNN_OP(CPU *cpu, uint16_t opcode){
    cpu->pc = opcode & 0x0FFF;
}
 
void opcode::CALL_2NNN_OP(CPU *cpu, uint16_t opcode){
    cpu->pile.push_back(cpu->pc);
    cpu->pc = opcode & 0x0FFF;
}

void opcode::SE_3XNN_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
        cpu->pc += 2;
    }
    cpu->pc += 2;

}

void opcode::SNE_4XNN_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
        cpu->pc += 4;
    } else {
        cpu->pc += 2;
    }
}

void opcode::SE_5XY0_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x0F00) >> 8] == cpu->registre[(opcode & 0x00F0) >> 4]) {
        cpu->pc += 4;
    } else {
        cpu->pc += 2;
    }
}

void opcode::LD_6XNN_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    cpu->pc += 2;
}

void opcode::ADD_7XNN_OP(CPU *cpu, uint16_t opcode){
    std::cout << cpu->toHexString(opcode) << std::endl;
    cpu->registre[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
    cpu->pc += 2;
}

void opcode::LD_8XY0_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] = cpu->registre[(opcode & 0x00F0) >> 4];
    cpu->pc += 2;
}

void opcode::OR_8XY1_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] |= cpu->registre[(opcode & 0x00F0) >> 4];
    cpu->pc += 2;
}

void opcode::AND_8XY2_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] &= cpu->registre[(opcode & 0x00F0) >> 4];
    cpu->pc += 2;
}

void opcode::XOR_8XY3_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] ^= cpu->registre[(opcode & 0x00F0) >> 4];
    cpu->pc += 2;
}

void opcode::ADD_8XY4_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x0F00) >> 8] + cpu->registre[(opcode & 0x00F0) >> 4] > 255) {
        cpu->registre[0xF] = 1;
    } else {
        cpu->registre[0xF] = 0;
    }
    cpu->registre[(opcode & 0x0F00) >> 8] += cpu->registre[(opcode & 0x00F0) >> 4];
    cpu->pc += 2;
}

void opcode::SUB_8XY5_OP(CPU *cpu, uint16_t opcode){
    uint8_t x = (opcode & 0x0F00) >> 8;
    uint8_t y = (opcode & 0x00F0) >> 4;
    
    if (cpu->registre[x] > cpu->registre[y]) {
        cpu->registre[0xF] = 1; // Pas d'emprunt
    } else {
        cpu->registre[0xF] = 0; // Emprunt
    }

    cpu->registre[x] -= cpu->registre[y];
    cpu->pc += 2;
}
void opcode::SHR_8XY6_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[0xF] = cpu->registre[(opcode & 0x0F00) >> 8] & 0x1;
    cpu->registre[(opcode & 0x0F00) >> 8] >>= 1;
    cpu->pc += 2;
}



void opcode::SUBN_8XY7_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x00F0) >> 4] > cpu->registre[(opcode & 0x0F00) >> 8]) {
        cpu->registre[0xF] = 1;
    } else {
        cpu->registre[0xF] = 0;
    }
    cpu->registre[(opcode & 0x0F00) >> 8] = cpu->registre[(opcode & 0x00F0) >> 4] - cpu->registre[(opcode & 0x0F00) >> 8];
    cpu->pc += 2;
}

void opcode::SHL_8XYE_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[0xF] = cpu->registre[(opcode & 0x0F00) >> 8] >> 7;
    cpu->registre[(opcode & 0x0F00) >> 8] <<= 1;
    cpu->pc += 2;
}

void opcode::SNE_9XY0_OP(CPU *cpu, uint16_t opcode){
    if (cpu->registre[(opcode & 0x0F00) >> 8] != cpu->registre[(opcode & 0x00F0) >> 4]) {
        cpu->pc += 4;
    } else {
        cpu->pc += 2;
    }
}

void opcode::LD_ANNN_OP(CPU *cpu, uint16_t opcode){
    cpu->I = opcode & 0x0FFF;
    cpu->pc += 2;
}

void opcode::JP_BNNN_OP(CPU *cpu, uint16_t opcode){
    cpu->pc = cpu->registre[0] + (opcode & 0x0FFF);
}

void opcode::RND_CXNN_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] = (rand() % 256) & (opcode & 0x00FF);
    cpu->pc += 2;
}

void opcode::DRW_DXYN_OP(CPU *cpu, uint16_t opcode, Grid *grid){
    grid->OP_DXYN(cpu->registre[(opcode & 0x0F00) >> 6], cpu->registre[(opcode & 0x00F0) >> 4], opcode & 0x000F, cpu);
    cpu->pc += 2;


}

// A faire ----------------------------------------------

void opcode::SKP_EX9E_OP(CPU *cpu, uint16_t opcode){
    if (cpu->touche[cpu->registre[(opcode & 0x0F00) >> 6]] == 1){
        cpu->pc += 2;
    }
    cpu->pc += 2;

}

void opcode::SKNP_EXA1_OP(CPU *cpu, uint16_t opcode){
    if (cpu->touche[cpu->registre[(opcode & 0x0F00) >> 6]] == 0){
        cpu->pc += 2;
    }
    cpu->pc += 2;

}


void opcode::LD_FX07_OP(CPU *cpu, uint16_t opcode){
    cpu->registre[(opcode & 0x0F00) >> 8] = cpu->delay_timer;
    cpu->pc += 2;
}


void opcode::LD_FX0A_OP(CPU *cpu, uint16_t opcode){
    cpu->pc += 2;
}

// A faire ----------------------------------------------

void opcode::LD_FX15_OP(CPU *cpu, uint16_t opcode){
    cpu->delay_timer = cpu->registre[(opcode & 0x0F00) >> 8];
    cpu->pc += 2;
}

void opcode::LD_FX18_OP(CPU *cpu, uint16_t opcode){
    cpu->sound_timer = cpu->registre[(opcode & 0x0F00) >> 8];
    cpu->pc += 2;
}

void opcode::ADD_FX1E_OP(CPU *cpu, uint16_t opcode){
    if (cpu->I + cpu->registre[(opcode & 0x0F00) >> 8] > 0xFFF) {
        cpu->registre[0xF] = 1;
    } else {
        cpu->registre[0xF] = 0;
    }
    cpu->I += cpu->registre[(opcode & 0x0F00) >> 8];
    cpu->pc += 2;
}

void opcode::LD_FX29_OP(CPU *cpu, uint16_t opcode){
    cpu->I = cpu->registre[(opcode & 0x0F00) >> 8] * 0x5;
    cpu->pc += 2;
}

void opcode::LD_FX33_OP(CPU *cpu, uint16_t opcode){
    cpu->memory[cpu->I] = cpu->registre[(opcode & 0x0F00) >> 8] / 100;
    cpu->memory[cpu->I + 1] = (cpu->registre[(opcode & 0x0F00) >> 8] / 10) % 10;
    cpu->memory[cpu->I + 2] = cpu->registre[(opcode & 0x0F00) >> 8] % 10;
    cpu->pc += 2;
}

void opcode::LD_FX55_OP(CPU *cpu, uint16_t opcode){
    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
        cpu->memory[cpu->I + i] = cpu->registre[i];
    }
    cpu->I += ((opcode & 0x0F00) >> 8) + 1;
    cpu->pc += 2;
}

void opcode::LD_FX65_OP(CPU *cpu, uint16_t opcode){
    for (int i = 0; i <= ((opcode & 0x0F00) >> 8); i++) {
        cpu->registre[i] = cpu->memory[cpu->I + i];
    }
    cpu->I += ((opcode & 0x0F00) >> 8) + 1;
    cpu->pc += 2;
}




void opcode::DecodOpcode(CPU *cpu, uint16_t opcode, Grid *grid) {
    uint8_t action;
    action = GetAction(opcode, cpu);

    switch (action){
        case 1: // 00E0
            std::cout << "00E0 CLS" << std::endl;
            CLS_00E0_OP(cpu, grid);
            break;

        case 2: // 00EE
            std::cout << "00EE RET" << std::endl;
            RET_00EE_OP(cpu);
            break;

        case 3: // 1NNN
            std::cout << "1NNN JP" << std::endl;
            JP_1NNN_OP(cpu, opcode);
            break;
        
        case 4: // 2NNN
            std::cout << "2NNN CALL" << std::endl;
            CALL_2NNN_OP(cpu, opcode);
            break;

        case 5: // 3XNN
            std::cout << "3XNN SE" << std::endl;
            SE_3XNN_OP(cpu, opcode);
            break;
        
        case 6: // 4XNN
            std::cout << "4XNN SNE" << std::endl;
            SNE_4XNN_OP(cpu, opcode);
            break;
        
        case 7: // 5XY0
            std::cout << "5XY0 SE" << std::endl;
            SE_5XY0_OP(cpu, opcode);
            break;

        case 8: // 6XNN
            std::cout << "6XNN LD" << std::endl;
            LD_6XNN_OP(cpu, opcode);
            break;
        
        case 9: // 7XNN
            std::cout << "7XNN ADD" << std::endl;
            ADD_7XNN_OP(cpu, opcode);
            break;
        
        case 10: // 8XY0
            std::cout << "8XY0 LD" << std::endl;
            LD_8XY0_OP(cpu, opcode);
            break;

        case 11: // 8XY1
            std::cout << "8XY1 OR" << std::endl;
            OR_8XY1_OP(cpu, opcode);
            break;
        
        case 12: // 8XY2
            std::cout << "8XY2 AND" << std::endl;
            AND_8XY2_OP(cpu, opcode);
            break;
        
        case 13: // 8XY3
            std::cout << "8XY3 XOR" << std::endl;
            XOR_8XY3_OP(cpu, opcode);
            break;

        case 14: // 8XY4
            std::cout << "8XY4 ADD" << std::endl;
            ADD_8XY4_OP(cpu, opcode);
            break;

        case 15: // 8XY5
            std::cout << "8XY5 SUB" << std::endl;
            SUB_8XY5_OP(cpu, opcode);
            break;

        case 16: // 8XY6
            std::cout << "8XY6 SHR" << std::endl;
            SHR_8XY6_OP(cpu, opcode);
            break;

        case 17: // 8XY7
            std::cout << "8XY7 SUBN" << std::endl;
            SUBN_8XY7_OP(cpu, opcode);
            break;

        case 18: // 8XYE
            std::cout << "8XYE SHL" << std::endl;
            SHL_8XYE_OP(cpu, opcode);
            break;

        case 19: // 9XY0
            std::cout << "9XY0 SNE" << std::endl;
            SNE_9XY0_OP(cpu, opcode);
            break;

        case 20: // ANNN
            std::cout << "ANNN LD" << std::endl;
            LD_ANNN_OP(cpu, opcode);
            break;

        case 21: // BNNN
            std::cout << "BNNN JP" << std::endl;
            JP_BNNN_OP(cpu, opcode);
            break;

        case 22: // CXNN
            std::cout << "CXNN RND" << std::endl;
            RND_CXNN_OP(cpu, opcode);
            break;

        case 23: // DXYN
            std::cout << "DXYN DRW" << std::endl;
            DRW_DXYN_OP(cpu, opcode, grid);
            break;

        case 24: // EX9E
            std::cout << "EX9E SKP" << std::endl;
            SKP_EX9E_OP(cpu, opcode);
            std::cout << "A FAIRE" << std::endl; 
            break;

        case 25: // EXA1
            std::cout << "EXA1 SKNP" << std::endl;
            std::cout << "A FAIRE" << std::endl; 

            SKNP_EXA1_OP(cpu, opcode);
            break;

        case 26: // FX07
            std::cout << "FX07 LD" << std::endl;
            LD_FX07_OP(cpu, opcode);
            break;

        case 27: // FX0A
            std::cout << "FX0A LD" << std::endl;
            LD_FX0A_OP(cpu, opcode);
            break;

        case 28: // FX15
            std::cout << "FX15 LD" << std::endl;
            LD_FX15_OP(cpu, opcode);
            break;

        case 29: // FX18
            std::cout << "FX18 LD" << std::endl;
            LD_FX18_OP(cpu, opcode);
            break;

        case 30: // FX1E
            std::cout << "FX1E ADD" << std::endl;
            ADD_FX1E_OP(cpu, opcode);
            break;

        case 31: // FX29
            std::cout << "FX29 LD" << std::endl;
            LD_FX29_OP(cpu, opcode);
            break;

        case 32: // FX33
            std::cout << "FX33 LD" << std::endl;
            LD_FX33_OP(cpu, opcode);
            break;

        case 33: // FX55
            std::cout << "FX55 LD" << std::endl;
            LD_FX55_OP(cpu, opcode);
            break;

        case 34: // FX65
            std::cout << "FX65 LD" << std::endl;
            LD_FX65_OP(cpu, opcode);
            break;      
    
    default:

        std::cout << "Error: Opcode not found"<< opcode << std::endl;
        cpu->pc += 2;

        break;
    }
}
