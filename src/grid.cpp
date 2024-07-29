#include "../include/grid.h"
#include <iostream>
#include <cstring>
#include <SDL.h>
#include "../include/cpu.h"

Grid::Grid() {
    numRows = 32;
    numCols = 64;
    cellSize = 13;
    initialize();
}

int Y = 19;

void Grid::print(SDL_Renderer* renderer) {
    for (int column = 0; column < numCols; column++) {
        for (int row = 0; row < numRows; row++) {
            SDL_Rect rect = { column * cellSize, row * cellSize + Y, cellSize, cellSize };
            if (grid[column][row] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); // White color
                SDL_RenderDrawRect(renderer, &rect);
            }
            if (grid[column][row] == 1) {
                SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE); // Black color
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}



void Grid::OP_DXYN(int x, int y, int n_pixel, CPU *cpu) {
    cpu->registre[0xf] = 0;
    for(int N = 0; N < n_pixel; N++) {
        uint8_t All_pixel = cpu->memory[cpu->I + N];

        for(int height = 0; height < 8; height++) {
            uint8_t pixel = All_pixel >> (7 - height) & 0b00000001;      
           

            if (pixel == 1) {
                if (grid[(x + height)][(y + N)] == 1) {
                    grid[(x + height)][(y + N)] = 0;
                    cpu->registre[0xf] = 1;
                }
            
                else {
                    grid[(x + height)][(y + N)] = 1;
                }
            }
        }
    }
}


void Grid::placePixels(int col, int row) {
    grid[col][row] = 1;
}

void Grid::initialize() {
    std::memset(grid, 0, sizeof(grid));
}

void Grid::clearGrid() {
    std::memset(grid, 0, sizeof(grid));
}
