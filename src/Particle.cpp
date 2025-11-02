#include "../include/raylib.h"
#include <vector>
#include <cmath>
#include "config.h"
#include "../include/raymath.h"

class Particle {
   public:
	Vector2 pos;
	int radius;
	Vector2 speed;
	Vector2 acceleration;
	Color color;
	bool active;

	Particle(Vector2 pos, int radius, Vector2 speed, Vector2 acceleration, Color color, bool active)
	    : pos(pos), radius(radius), speed(speed), acceleration(acceleration), color(color), active(active) {}

	void draw() {
		DrawCircle(pos.x, pos.y, radius, color);
	}

	void update(float dt) {
		speed.x += acceleration.x * dt;
		speed.y += acceleration.y * dt;
		pos.x += speed.x;
		pos.y += speed.y;
	}

	void checkCollision(std::vector<Particle>& particles, int index) {
		// Rebote con bordes + corrección de posición
		if (pos.x < 0) {
			pos.x = 0;
			speed.x *= -ENERGY_LOSS;
		}
		if (pos.x + radius > SCREEN_WIDTH) {
			pos.x = SCREEN_WIDTH - radius;
			speed.x *= -ENERGY_LOSS;
		}

		if (pos.y < 0) {
			pos.y = 0;
			speed.y *= -ENERGY_LOSS;
		}
		if (pos.y + radius > SCREEN_HEIGHT) {
			pos.y = SCREEN_HEIGHT - radius;
			speed.y *= -ENERGY_LOSS;
		}

		for (int j = index + 1; j < particles.size(); j++) {
			Particle& other = particles[j];
			float dx = other.pos.x - pos.x;
			float dy = other.pos.y - pos.y;
			float distance = sqrt(dx * dx + dy * dy);
			float minDistance = radius + other.radius;
			if (distance < minDistance) {
				auto normal = Vector2Normalize(Vector2Subtract(other.pos, this->pos));
				auto relativeVel = Vector2Subtract(other.speed, this->speed);
				auto impulse = Vector2Scale(normal, 2 * Vector2DotProduct(relativeVel, normal) / 2);

				auto repulsion = Vector2Scale(normal, minDistance - distance);

				// Intercambiar velocidades simple
				this->speed += impulse;
				other.speed -= impulse;

				this->speed -= repulsion;
				other.speed += repulsion;
			}
		}
	}
};