#pragma once
#include <vector>
#include "../include/cpu.h"
#include <SDL.h>

class Grid{
    public:
        Grid();
        void initialize();
        void print(SDL_Renderer* renderer);
        void OP_DXYN(int x, int y, int n, CPU *cpu);
        void placePixels(int x = 0, int y = 0);
        void clearGrid();

        int grid[64][32];

    private:
        int numRows;
        int numCols;
        int cellSize;
};