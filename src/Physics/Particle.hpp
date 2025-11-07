#pragma once

#include <vector>

#include "../config.h"
#include "Cube.hpp"
#include "PhysicsSolver.hpp"

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

	PhysicsSolver physicsSolver;

	bool active;

	Particle(Vector3 pos, Vector3 speed, Vector3 acceleration,
			 Color color, float radius, bool active)
		: pos(pos),
		  speed(speed),
		  acceleration(acceleration),
		  color(color),
		  radius(radius),
		  active(active) {
		this->mass = radius * 1000;
	}

	void applyForce(Vector3 force, float dt);

	void update(float dt);

	void draw();

	void checkCollision(std::vector<Particle>* particles, Cube boundary, int index);

	void solveCollition(Particle& other);
};
