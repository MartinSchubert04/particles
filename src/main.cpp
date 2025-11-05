#include "../include/raylib.h"
#include "InputHandler.cpp"
#include "Particle.h"
#include "config.h"

void updateFrame();
void InitEntities();
void updateGame();

static const int fontSize = 40;
static const int fpsTarget = 60;

Rectangle getNewRectangle();
std::vector<Particle> particles;

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Conways's game of life");

	InitEntities();

	SetTargetFPS(fpsTarget);

	// Main game loop
	while (!WindowShouldClose())  // Detect window close button or ESC key
	{
		updateFrame();
	}

	// De-Initialization
	CloseWindow();	// Close window and OpenGL context

	return 0;
}

void InitEntities() {
	// for (Player& p : player) {
	// 	p.rec.x = std::round(((float)SCREEN_WIDTH / 2) + GetRandomValue(-50,
	// 50)); 	p.rec.y = std::round(((float)SCREEN_HEIGHT / 2));  //+
	// GetRandomValue(-50, 50)); 	p.rec.width = CELL_SIZE; 	p.rec.height =
	// CELL_SIZE; 	p.speed.x = GetRandomValue(4, 8); 	p.speed.y =
	// GetRandomValue(4, 8); 	p.color = RAYWHITE;
	// }

	// for (int i = 0; i < NUM_MAX_SQUARES; i++) {
	// 	Player& p = players[i];

	// 	p.rec.x = std::round(((float)SCREEN_WIDTH / 2) + GetRandomValue(-50,
	// 50)); 	p.rec.y = std::round(((float)SCREEN_HEIGHT / 2));  //+
	// GetRandomValue(-50, 50)); 	p.rec.width = CELL_SIZE; 	p.rec.height =
	// CELL_SIZE; 	i = 0 ? p.speed.x = 8 : p.speed.x = 0; 	p.speed.y =
	// GetRandomValue(4, 8); 	p.color = RAYWHITE;
	// }
}

void updateGame() {
	// Player movement
	float dt = 1.0 / 60.0;

	checkInputs(particles, dt);

	for (int i = 0; i < particles.size(); i++) {
		particles[i].applyForce(G, dt);
		particles[i].update(dt);
		particles[i].checkCollision(particles, i);
	}
}

void updateDraw() {
	BeginDrawing();	 // Init the state before draw calls

	ClearBackground(BLACK);

	for (Particle& p : particles) {
		p.draw();
	}

	DrawText(TextFormat("FPS: %i", GetFPS()), 0, 0,
			 fontSize, Fade(WHITE, 0.5));
	DrawText(TextFormat("Ball count: %i", particles.size()), 0, fontSize, fontSize,
			 Fade(WHITE, 0.5));

	EndDrawing();
}

void updateFrame() {
	updateGame();
	updateDraw();
}