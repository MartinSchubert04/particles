#include <vector>

#include "../include/raylib.h"
#include "InputHandler.cpp"
#include "Particle.h"

void UpdateGame();
void UpdateDraw();

static const std::vector<Particle> particles;

int main() {
	const int screenWidth = 1024;
	const int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "Raylib 3D Example");

	// Define the camera to look into our 3D world
	Camera3D camera = {0};
	camera.position = (Vector3){0.0f, 10.0f, 10.0f};  // Camera position
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};	  // Camera looking at point
	camera.up = (Vector3){0.0f, 0.5f, 0.0f};		  // Camera up vector (relative to target)
	camera.fovy = 45.0f;							  // Camera field-of-view in Y direction
	camera.projection = CAMERA_PERSPECTIVE;			  // Camera projection type

	SetTargetFPS(60);  // Set our game to run at 60 frames-per-second

	while (!WindowShouldClose())  // Detect window close button or ESC key
	{
		// Update camera (optional, for movement)
		UpdateCamera(&camera, CAMERA_THIRD_PERSON);	 // Example: Free camera controls

		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode3D(camera);

		UpdateGame();
		UpdateDraw();

		DrawGrid(10, 1.0f);									 // Draw a grid for reference
		DrawSphere((Vector3){0.0f, 0.5f, 0.0f}, 1.0f, RED);	 // Draw a red cube

		EndMode3D();

		DrawFPS(10, 10);  // Display FPS

		EndDrawing();
	}

	CloseWindow();	// Close window and unload OpenGL context

	return 0;
}

void UpdateGame() {
	checkInputs();
}
void UpdateDraw() {
}