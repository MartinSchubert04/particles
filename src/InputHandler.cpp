#pragma once
#include "../include/lib.h"
#include "Physics/Particle.hpp"

class InputHandler {
   public:
	void check(std::vector<Particle>* particles, float dt, Camera3D camera) {
		mouseInputs(*particles, dt, camera);
		keyInputs(*particles);
	}
	void mouseInputs(std::vector<Particle>& particles, float dt, Camera3D camera) {
		float particleSize = GetRandomValue(10, 15);

		// if (IsKeyPressed(KEY_SPACE)) {
		// 	particles.push_back({{(float)GetRandomValue(-100, 100), 0, (float)GetRandomValue(-100, 100)},
		// 						 {(float)GetRandomValue(-2, 2), 0, (float)GetRandomValue(-2, 2)},
		// 						 {0, 0, 0},
		// 						 MAGENTA,
		// 						 (float)particleSize,
		// 						 true});
		// }

		if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
			int mouseCircleRadius = 60;
			Vector3 mousePos = {camera.target.x, camera.target.y, camera.target.z};

			DrawSphereWires({camera.target.x, camera.target.y, camera.target.z}, mouseCircleRadius, 10, 10, GREEN);

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
