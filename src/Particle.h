#pragma once

#include <cmath>
#include <vector>

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "config.h"

class Particle {
   private:
	float maxSpeed = 3.0f;

   public:
	Vector3 pos;
	int radius;
	Vector3 speed;
	Vector3 acceleration;
	float mass;
	Color color;

	bool active;

	Particle(Vector3 pos, Vector3 speed, Vector3 acceleration,
			 Color color, float mass, bool active)
		: pos(pos),
		  speed(speed),
		  acceleration(acceleration),
		  color(color),
		  mass(mass),
		  active(active) {
		this->radius = mass * 3;
	}

	void applyForce(Vector3 force, float dt) {
		speed += Vector3Scale(force, dt);

		if (Vector3Length(speed) > maxSpeed)
			speed = Vector3Scale(Vector3Normalize(speed), maxSpeed);
	}

	void update(float dt) {
		pos += speed;
	}

	void draw() {
		DrawSphere(pos, radius, color);
	}

	void checkCollision(std::vector<Particle>& particles, int index) {
		// Rebote con bordes + corrección de posición
		if (pos.x - radius < 0) {
			pos.x = 0 + radius;
			speed.x *= -ENERGY_LOSS;
		}
		if (pos.x + radius > SCREEN_WIDTH) {
			pos.x = SCREEN_WIDTH - radius;
			speed.x *= -ENERGY_LOSS;
		}

		if (pos.y - radius < 0) {
			pos.y = 0 + radius;
			speed.y *= -ENERGY_LOSS;
		}
		if (pos.y + radius > SCREEN_HEIGHT) {
			pos.y = SCREEN_HEIGHT - radius;
			speed.y *= -ENERGY_LOSS;
		}

		for (int j = index + 1; j < particles.size(); j++) {
			Particle& other = particles[j];
			float distance = Vector3Distance(this->pos, other.pos);
			float minDistance = radius + other.radius;
			if (distance < minDistance) {
				auto normal = Vector3Normalize(Vector3Subtract(other.pos, this->pos));
				auto relativeVel = Vector3Subtract(other.speed, this->speed);
				auto impulse = Vector3Scale(normal, 2 * Vector3DotProduct(relativeVel, normal) / (this->mass + other.mass));

				auto repulsion = Vector3Scale(normal, minDistance - distance);

				// Intercambiar velocidades simple
				this->speed += Vector3Scale(impulse, 1 / mass);
				other.speed -= Vector3Scale(impulse, 1 / other.mass);

				this->speed -= Vector3Scale(repulsion, 1 / mass);
				other.speed += Vector3Scale(repulsion, 1 / other.mass);
			}
		}
	}
};
