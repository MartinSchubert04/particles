#include "../include/raylib.h"
#include <cstring>
#include <random>

void updateFrame();
void InitEntities();
void updateGame();

#define NUM_MAX_SQUARES 2

#define GRID_WIDTH 40
#define GRID_HEIGHT 15
#define CELL_SIZE 10
#define SPEED 5
#define ENERGY_LOSS 0.9
#define G 9.81

static const int screenWidth = 800;
static const int screenHeight = 450;

static const int fontSize = 40;
static const int fpsTarget = 60;

Rectangle getNewRectangle();

typedef struct Player {
	Rectangle rec;
	Vector2 speed;
	Vector2 acceleration;
	Color color;
	bool active;
} Player;

std::vector<Player> players;

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
	CloseWindow();  // Close window and OpenGL context

	return 0;
}

void InitEntities() {
	// for (Player& p : player) {
	// 	p.rec.x = std::round(((float)screenWidth / 2) + GetRandomValue(-50, 50));
	// 	p.rec.y = std::round(((float)screenHeight / 2));  //+ GetRandomValue(-50, 50));
	// 	p.rec.width = CELL_SIZE;
	// 	p.rec.height = CELL_SIZE;
	// 	p.speed.x = GetRandomValue(4, 8);
	// 	p.speed.y = GetRandomValue(4, 8);
	// 	p.color = RAYWHITE;
	// }

	// for (int i = 0; i < NUM_MAX_SQUARES; i++) {
	// 	Player& p = players[i];

	// 	p.rec.x = std::round(((float)screenWidth / 2) + GetRandomValue(-50, 50));
	// 	p.rec.y = std::round(((float)screenHeight / 2));  //+ GetRandomValue(-50, 50));
	// 	p.rec.width = CELL_SIZE;
	// 	p.rec.height = CELL_SIZE;
	// 	i = 0 ? p.speed.x = 8 : p.speed.x = 0;
	// 	p.speed.y = GetRandomValue(4, 8);
	// 	p.color = RAYWHITE;
	// }
}

void updateGame() {
	// Player movement
	float dt = GetFrameTime();

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		DrawRectangle(GetMouseX(), GetMouseY(), CELL_SIZE, CELL_SIZE, WHITE);

		players.push_back({{(float)GetMouseX(), (float)GetMouseY(), (float)CELL_SIZE, (float)CELL_SIZE},
		                   {SPEED, SPEED},
		                   {0, G},
		                   WHITE,
		                   true});
	}

	for (int i = 0; i < players.size(); i++) {
		Player& p = players[i];

		// Mover
		p.speed.x += p.acceleration.x * dt;
		p.speed.y += p.acceleration.y * dt;

		p.speed.x *= 0.99f;  // 1.0 = sin fricción, 0.9 = mucha fricción
		p.speed.y *= 0.99f;

		p.rec.x += p.speed.x;
		p.rec.y += p.speed.y;

		// Rebote con bordes + corrección de posición
		if (p.rec.x < 0) {
			p.rec.x = 0;
			p.speed.x *= -ENERGY_LOSS;
		}
		if (p.rec.x + p.rec.width > screenWidth) {
			p.rec.x = screenWidth - p.rec.width;
			p.speed.x *= -ENERGY_LOSS;
		}

		if (p.rec.y < 0) {
			p.rec.y = 0;
			p.speed.y *= -ENERGY_LOSS;
		}
		if (p.rec.y + p.rec.height > screenHeight) {
			p.rec.y = screenHeight - p.rec.height;
			p.speed.y *= -ENERGY_LOSS;
		}

		// Colisiones entre cuadrados
		for (int j = i + 1; j < players.size(); j++) {
			Player& b = players[j];

			if (CheckCollisionRecs(p.rec, b.rec)) {
				float temp = p.speed.x;
				p.speed.x = b.speed.x;
				b.speed.x = temp;
			}
		}
	}
}

void updateDraw() {
	BeginDrawing();  // Init the state before draw calls

	ClearBackground(BLACK);

	int offsetY = (screenHeight / 2) - (GRID_HEIGHT * CELL_SIZE / 2);
	int offsetX = (screenWidth / 2) - (GRID_WIDTH * CELL_SIZE / 2);

	for (int i = 0; i < players.size(); i++) {
		if (i < players.size()) {
			// Color color = grid[y][x].active ? RAYWHITE : BLACK;
			DrawCircle((players[i].rec.x), (players[i].rec.y), (float)CELL_SIZE / 2, WHITE);
		}
	}

	DrawText(TextFormat("FPS: %i", GetFPS()), 0, screenHeight - fontSize, fontSize, Fade(WHITE, 0.2));
	DrawText(TextFormat("Ball count: %i", players.size()), 0, 0, fontSize, Fade(WHITE, 0.2));

	EndDrawing();
}

void updateFrame() {
	updateGame();
	updateDraw();
}