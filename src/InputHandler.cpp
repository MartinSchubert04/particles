#pragma once
#include "../include/raylib.h"
#include "Particle.h"

void checkInputs(std::vector<Particle>& particles, float dt) {
	int particleSize = GetRandomValue(1, 2);

	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		particles.push_back({{(float)GetMouseX(), (float)GetMouseY()},
							 {0, 0},
							 {0, 0},
							 WHITE,
							 (float)particleSize,
							 true});
	}

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		int mouseCircleRadius = 80;
		Vector2 mousePos = {(float)GetMouseX(), (float)GetMouseY()};

		DrawCircleLines(mousePos.x, mousePos.y, mouseCircleRadius, GREEN);

		for (int j = 0; j < particles.size(); j++) {
			Particle& p = particles[j];

			Vector2 dir = Vector2Subtract(mousePos, p.pos);
			float distance = Vector2Length(dir);

			if (distance < mouseCircleRadius && distance > 1.0f) {
				// Normalizamos la dirección
				Vector2 direction = Vector2Normalize(dir);
				DrawLineV(p.pos, Vector2Add(p.pos, Vector2Scale(direction, 40)), RED);

				// Magnitud de la fuerza: más cerca, más fuerte
				float strength = 60000.0f;

				// Aplicamos fuerza hacia el mouse
				Vector2 force = Vector2Scale(direction, strength);

				p.applyForce(force, dt);
			}
		}
	}
}