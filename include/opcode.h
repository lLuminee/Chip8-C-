#pragma once
#include <cstdint>
#include <iostream>
#include "cpu.h"
#include "grid.h"

class opcode
{


public:

void DecodOpcode(CPU *cpu, uint16_t opcode, Grid *grid);
void initializeOpcodeMask();



private:

void CLS_00E0_OP(CPU *cpu, Grid *grid);
void RET_00EE_OP(CPU *cpu);
void SYS_0NNN_OP(CPU *cpu, uint16_t opcode);
void JP_1NNN_OP(CPU *cpu, uint16_t opcode);
void CALL_2NNN_OP(CPU *cpu, uint16_t opcode);
void SE_3XNN_OP(CPU *cpu, uint16_t opcode);
void SNE_4XNN_OP(CPU *cpu, uint16_t opcode);
void SE_5XY0_OP(CPU *cpu, uint16_t opcode);
void LD_6XNN_OP(CPU *cpu, uint16_t opcode);
void ADD_7XNN_OP(CPU *cpu, uint16_t opcode);
void LD_8XY0_OP(CPU *cpu, uint16_t opcode);
void OR_8XY1_OP(CPU *cpu, uint16_t opcode);
void AND_8XY2_OP(CPU *cpu, uint16_t opcode);
void XOR_8XY3_OP(CPU *cpu, uint16_t opcode);
void ADD_8XY4_OP(CPU *cpu, uint16_t opcode);
void SUB_8XY5_OP(CPU *cpu, uint16_t opcode);
void SHR_8XY6_OP(CPU *cpu, uint16_t opcode);
void SUBN_8XY7_OP(CPU *cpu, uint16_t opcode);
void SHL_8XYE_OP(CPU *cpu, uint16_t opcode);
void SNE_9XY0_OP(CPU *cpu, uint16_t opcode);
void LD_ANNN_OP(CPU *cpu, uint16_t opcode);
void JP_BNNN_OP(CPU *cpu, uint16_t opcode);
void RND_CXNN_OP(CPU *cpu, uint16_t opcode);
void DRW_DXYN_OP(CPU *cpu, uint16_t opcode, Grid *grid);
void SKP_EX9E_OP(CPU *cpu, uint16_t opcode);
void SKNP_EXA1_OP(CPU *cpu, uint16_t opcode);
void LD_FX07_OP(CPU *cpu, uint16_t opcode);
void LD_FX0A_OP(CPU *cpu, uint16_t opcode);
void LD_FX15_OP(CPU *cpu, uint16_t opcode);
void LD_FX18_OP(CPU *cpu, uint16_t opcode);
void ADD_FX1E_OP(CPU *cpu, uint16_t opcode);
void LD_FX29_OP(CPU *cpu, uint16_t opcode);
void LD_FX33_OP(CPU *cpu, uint16_t opcode);
void LD_FX55_OP(CPU *cpu, uint16_t opcode);
void LD_FX65_OP(CPU *cpu, uint16_t opcode);


};