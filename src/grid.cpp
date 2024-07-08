#include "../include/grid.h"
#include <iostream>
#include <cstring>
#include "raylib.h"
#include "../include/cpu.h"

Grid::Grid(){
    numRows = 32;
    numCols = 64;
    cellSize = 13;
    initialize();
}

void Grid::print(){

    for (int column = 0; column < numCols; column++) {
        for(int row = 0; row < numRows;row++) {
            if (grid[column][row] == 0){
                DrawRectangle(column * cellSize +1, row * cellSize + 1, cellSize -1, cellSize -1, WHITE);

            }
            if (grid[column][row] == 1){
                DrawRectangle(column * cellSize +1, row * cellSize + 1, cellSize -1, cellSize -1, BLACK);

            }

        }
    }

}

void Grid::placePixels(int col, int raw) {
    grid[col][raw] = 1;
}

void Grid::OP_DXYN(int x, int y, int n, CPU *cpu) {
    uint8_t All_pixel = cpu->memory[cpu->I];
    for(int N = 0; N < n; N++) {
        for(int height = 0; height < 8; height++) {
            uint8_t pixel = All_pixel >> (7 - height) & 0b0001;              

            if (pixel == 1) {
                if (grid[(x + height)][(y + N)] == 1) {
                    grid[(x + height)][(y + N)] = 0;
                    cpu->registre[0xf] = 0;
                }
            
                else {
                    grid[(x + height)][(y + N)] = 1;
                }
            }

            if (pixel == 0) {
                grid[(x + height)][(y + N)] = 0;
            }
            
        }
    }
}

void Grid::initialize() {
    std::memset(grid, 0, sizeof(grid));
}

void Grid::clearGrid() {
    std::memset(grid, 0, sizeof(grid));
}
