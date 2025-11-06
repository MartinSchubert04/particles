#pragma once
#include "../include/raylib.h"
#include "Particle.h"

class InputHandler {
   public:
	void check(std::vector<Particle>& particles, float dt, Camera3D camera) {
		mouseInputs(particles, dt, camera);
		keyInputs(particles);
	}
	void mouseInputs(std::vector<Particle>& particles, float dt, Camera3D camera) {
		float particleSize = 0.5;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			particles.push_back({{0, 0, 0.0f},
								 {0.3, 0, 0.6},
								 {0, 0, 0},
								 WHITE,
								 (float)particleSize,
								 true});
		}

		if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
			int mouseCircleRadius = 80;
			Vector3 mousePos = {(float)GetMouseX(), (float)GetMouseY()};

			DrawCircleLines(mousePos.x, mousePos.y, mouseCircleRadius, GREEN);

			for (int j = 0; j < particles.size(); j++) {
				Particle& p = particles[j];

				Vector3 dir = Vector3Subtract(mousePos, p.pos);
				float distance = Vector3Length(dir);

				if (distance < mouseCircleRadius && distance > 1.0f) {
					// Normalizamos la dirección
					Vector3 direction = Vector3Normalize(dir);
					// DrawLineV(p.pos, Vector3Add(p.pos, Vector3Scale(direction, 40)), RED);

					// Magnitud de la fuerza: más cerca, más fuerte
					float strength = 60000.0f;

					// Aplicamos fuerza hacia el mouse
					Vector3 force = Vector3Scale(direction, strength);

					p.applyForce(force, dt);
				}
			}
		}
	}

	void keyInputs(std::vector<Particle>& particles) {
		if (IsKeyPressed(KEY_R)) {
			particles.clear();
		}
	}
};
