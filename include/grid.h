#pragma once
#include <vector>
#include "raylib.h"
#include "cpu.h"


class Grid{
    public:
        Grid();
        void initialize();
        void print();

        void placePixels(int x = 0, int y = 0);
        void OP_DXYN(int x, int y, int n, CPU *cpu);
        void clearGrid();

        int grid[64][32];

    private:
        int numRows;
        int numCols;
        int cellSize;
        std::vector<Color> color;
};