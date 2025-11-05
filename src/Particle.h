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
	Vector2 pos;
	int radius;
	Vector2 speed;
	Vector2 acceleration;
	float mass;
	Color color;

	bool active;

	Particle(Vector2 pos, Vector2 speed, Vector2 acceleration,
			 Color color, float mass, bool active)
		: pos(pos),
		  speed(speed),
		  acceleration(acceleration),
		  color(color),
		  mass(mass),
		  active(active) {
		this->radius = mass * 5;
	}

	void applyForce(Vector2 force, float dt) {
		speed += Vector2Scale(force, dt);

		if (Vector2Length(speed) > maxSpeed)
			speed = Vector2Scale(Vector2Normalize(speed), maxSpeed);
	}

	void update(float dt) {
		pos += speed;
	}

	void draw() {
		DrawCircle(pos.x, pos.y, radius, color);
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
			float distance = Vector2Distance(this->pos, other.pos);
			float minDistance = radius + other.radius;
			if (distance < minDistance) {
				auto normal = Vector2Normalize(Vector2Subtract(other.pos, this->pos));
				auto relativeVel = Vector2Subtract(other.speed, this->speed);
				auto impulse = Vector2Scale(normal, 2 * Vector2DotProduct(relativeVel, normal) / (this->mass + other.mass));

				auto repulsion = Vector2Scale(normal, minDistance - distance);

				// Intercambiar velocidades simple
				this->speed += Vector2Scale(impulse, 1 / mass);
				other.speed -= Vector2Scale(impulse, 1 / other.mass);

				this->speed -= Vector2Scale(repulsion, 1 / mass);
				other.speed += Vector2Scale(repulsion, 1 / other.mass);
			}
		}
	}
};
