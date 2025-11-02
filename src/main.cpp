/*******************************************************************************************
 *
 *   raylib [core] example - delta time
 *
 *   Example complexity rating: [★☆☆☆] 1/4
 *
 *   Example originally created with raylib 5.5, last time updated with raylib 5.6-dev
 *
 *   Example contributed by Robin (@RobinsAviary) and reviewed by Ramon Santamaria (@raysan5)
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2025 Robin (@RobinsAviary)
 *
 ********************************************************************************************/

#include "../include/raylib.h"
#include <cstring>
#include <random>

void updateFrame();
void InitEntities();
void updateGame();

#define NUM_MAX_SQUARES 5

#define GRID_WIDTH 40
#define GRID_HEIGHT 15
#define CELL_SIZE 10

static const int screenWidth = 800;
static const int screenHeight = 450;

static const int fontSize = 40;
static const int fpsTarget = 5;

int generation = 0;

Rectangle getNewRectangle();

typedef struct Cell {
	Rectangle rec;
	Vector2 speed;
	Color color;
	bool active;
} Cell;

static Cell cell[NUM_MAX_SQUARES] = {0};

static Cell grid[GRID_HEIGHT][GRID_WIDTH] = {0};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
	InitWindow(screenWidth, screenHeight, "Conways's game of life");

	InitEntities();

	SetTargetFPS(fpsTarget);

	// Main game loop
	while (!WindowShouldClose())  // Detect window close button or ESC key
	{
		updateFrame();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();  // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

void ClearGrid() {
	for (int y = 0; y < GRID_HEIGHT; y++)
		for (int x = 0; x < GRID_WIDTH; x++)
			grid[y][x].active = false;
}

void InitEntities() {
	for (Cell& p : cell) {  // Recorre cada elemento del array
		p.rec.x = (float)screenWidth / 2;
		p.rec.y = (float)screenHeight / 2;
		p.rec.width = CELL_SIZE;
		p.rec.height = CELL_SIZE;
		p.speed.x = 5;
		p.speed.y = 5;
		p.color = RAYWHITE;
	}

	ClearGrid();

	// Arrancan en 0
	// for (int y = 0; y < GRID_HEIGHT; y++) {
	// 	for (int x = 0; x < GRID_WIDTH; x++) {
	// 		grid[y][x].active = GetRandomValue(0, 1);  // inicial random
	// 	}
	// }

	// PATRONES

	// Gosper Glider Gun (ajustá offsets si se sale del grid)
	int ox = 20;
	int oy = 10;

	int pattern[][2] = {
	    {1, 0},
	    {2, 0},
	    {0, 1},
	    {1, 1},
	    {1, 2},
	};

	int numCells = sizeof(pattern) / sizeof(pattern[0]);
	for (int i = 0; i < numCells; i++) {
		int x = pattern[i][0] + ox;
		int y = pattern[i][1] + oy;
		if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT)
			grid[y][x].active = true;
	}
}

void updateGame() {
	// Player movement
	// for (Cell& c : cell) {
	// 	if (IsKeyDown(KEY_RIGHT)) c.rec.x += c.speed.x;
	// 	if (IsKeyDown(KEY_LEFT)) c.rec.x -= c.speed.x;
	// 	if (IsKeyDown(KEY_UP)) c.rec.y -= c.speed.y;
	// 	if (IsKeyDown(KEY_DOWN)) c.rec.y += c.speed.y;
	// }
	Cell nextGrid[GRID_HEIGHT][GRID_WIDTH] = {0};

	int offsets[8][2] = {
	    {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			int activeAroundCount = 0;

			for (auto& o : offsets) {
				int nx = x + o[0];
				int ny = y + o[1];
				// controlás los límites o usás módulo
				// y contás vecinos activos
				if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
					if (grid[ny][nx].active) activeAroundCount++;
				}
			}

			if (grid[y][x].active) {
				if (activeAroundCount < 2 || activeAroundCount > 3)
					nextGrid[y][x].active = false;  // muere
				else
					nextGrid[y][x].active = true;  // sigue viva
			} else {
				if (activeAroundCount == 3)
					nextGrid[y][x].active = true;  // nace
				else
					nextGrid[y][x].active = false;  // sigue muerta
			}
		}
	}

	memcpy(grid, nextGrid, sizeof(grid));

	generation += 1;
}

void updateDraw() {
	BeginDrawing();  // Init the state before draw calls

	ClearBackground(BLACK);

	int offsetY = (screenHeight / 2) - (GRID_HEIGHT * CELL_SIZE / 2);
	int offsetX = (screenWidth / 2) - (GRID_WIDTH * CELL_SIZE / 2);

	for (int y = 0; y < GRID_HEIGHT; y++) {
		for (int x = 0; x < GRID_WIDTH; x++) {
			Color color = grid[y][x].active ? RAYWHITE : BLACK;
			DrawRectangle((x * CELL_SIZE) + offsetX, (y * CELL_SIZE) + offsetY, CELL_SIZE, CELL_SIZE, color);
		}
	}

	DrawText(TextFormat("FPS: %i", GetFPS()), 0, screenHeight - fontSize, fontSize, Fade(WHITE, 0.2));
	DrawText(TextFormat("Gen: %i", generation), 0, 0, fontSize, Fade(WHITE, 0.2));

	EndDrawing();
}

void updateFrame() {
	updateGame();
	updateDraw();
}