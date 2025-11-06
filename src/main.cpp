#include <algorithm>
#include <iostream>
#include <vector>

#include "../include/raylib.h"
#include "Cube.h"
#include "InputHandler.cpp"
#include "Particle.h"

void updateGame();
void updateDraw();
void initState();
void updateFrame();

const int screenWidth = 1024;
const int screenHeight = 900;

static std::vector<Particle> particles;

static Cube boundary;

static Camera3D camera = {0};

static InputHandler inputHandler;

int main() {
	InitWindow(screenWidth, screenHeight, "Raylib 3D Example");

	initState();

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

	while (!WindowShouldClose())  // Detect window close button or ESC key
	{
		// Update camera (optional, for movement)
		UpdateCamera(&camera, CAMERA_THIRD_PERSON);	 // Example: Free camera controls
		HideCursor();
		SetMousePosition(screenWidth / 2, screenHeight / 2);
		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);

		updateFrame();

		EndMode3D();

		DrawFPS(10, 10);  // Display FPS
		DrawText(TextFormat("Ball count: %i", particles.size()), 10, 30, 20, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();	// Close window and unload OpenGL context

	return 0;
}

void initState() {
	// Define the camera to look into our 3D world
	camera = {
		(Vector3){0.0f, 10.0f, 70.0f},
		(Vector3){0.0f, 0.0f, 0.0f},
		(Vector3){0.0f, 0.5f, 0.0f},
		45.0f,
		CAMERA_PERSPECTIVE,
	};

	boundary = {
		{0, 0, 0},
		{
			30,
			30,
			30,
		},
		(Color){255, 255, 255, 50},
	};
}

void UpdateGame() {
	float dt = 1.0f / 6.0f;

	inputHandler.check(particles, dt, camera);

	for (unsigned int i; i < particles.size(); i++) {
		Particle& p = particles[i];

		p.applyForce(GRAVITY, dt);
		p.update(dt);
		p.checkCollision(particles, boundary, i);
	}
}
void UpdateDraw() {
	for (Particle& p : particles) {
		p.draw();
	}
	DrawGrid(boundary.size.x, 1.0f);  // Draw a grid for reference
	DrawCube(boundary.position, boundary.size.x, boundary.size.y, boundary.size.z, boundary.color);
}

void updateFrame() {
	UpdateGame();
	UpdateDraw();
}