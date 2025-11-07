#pragma once

#include <cmath>
#include <vector>

#include "../include/raylib.h"
#include "../include/raymath.h"
#include "Cube.h"
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

	void applyForce(Vector3 force, float dt);

	void update(float dt);

	void draw();

	void checkCollision(std::vector<Particle>& particles, Cube boundary, int index);
};
