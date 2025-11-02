// #include "patterns.h"

// // Acceso a la grilla definida externamente
// extern Cell grid[GRID_HEIGHT][GRID_WIDTH];

// void InitPatterns() {
//     // Limpiar toda la grilla
//     for (int y = 0; y < GRID_HEIGHT; y++)
//         for (int x = 0; x < GRID_WIDTH; x++)
//             grid[y][x].active = false;

//     // --- Block (Still Life) ---
//     grid[1][1].active = true;
//     grid[1][2].active = true;
//     grid[2][1].active = true;
//     grid[2][2].active = true;

//     // --- Blinker (Oscillator) ---
//     int midY = GRID_HEIGHT / 2;
//     int midX = GRID_WIDTH / 2;
//     grid[midY][midX - 1].active = true;
//     grid[midY][midX].active     = true;
//     grid[midY][midX + 1].active = true;

//     // --- Glider (Spaceship) ---
//     grid[5][2].active = true;
//     grid[6][3].active = true;
//     grid[7][1].active = true;
//     grid[7][2].active = true;
//     grid[7][3].active = true;

//     // --- Toad (Oscillator) ---
//     grid[midY + 1][midX].active     = true;
//     grid[midY + 1][midX + 1].active = true;
//     grid[midY + 1][midX + 2].active = true;
//     grid[midY + 2][midX - 1].active = true;
//     grid[midY + 2][midX].active     = true;
//     grid[midY + 2][midX + 1].active = true;

//     // --- Beacon (Oscillator) ---
//     grid[2][GRID_WIDTH - 4].active = true;
//     grid[2][GRID_WIDTH - 3].active = true;
//     grid[3][GRID_WIDTH - 4].active = true;
//     grid[3][GRID_WIDTH - 3].active = true;

//     grid[4][GRID_WIDTH - 2].active = true;
//     grid[4][GRID_WIDTH - 1].active = true;
//     grid[5][GRID_WIDTH - 2].active = true;
//     grid[5][GRID_WIDTH - 1].active = true;
// }
