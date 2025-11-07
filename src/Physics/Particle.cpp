#include "Particle.hpp"

#include "../../include/lib.h"

void Particle::applyForce(Vector3 force, float dt) {
	speed += Vector3Scale(force, dt);

	if (Vector3Length(speed) > maxSpeed)
		speed = Vector3Scale(Vector3Normalize(speed), maxSpeed);
}

void Particle::update(float dt) {
	lastPos = pos;
	speed += Vector3Scale(acceleration, dt);
	pos += Vector3Scale(speed, dt);
	acceleration = Vector3Zero();

	if (path.empty() || Vector3Distance(path.back(), pos) > 0.5f)
		path.push_back(pos);
}

void Particle::draw() {
	DrawSphereWires(pos, radius, 10, 10, color);

	for (int i = 1; i < path.size(); i++) {
		DrawLine3D(path[i - 1], path[i], BLUE);
	}
}

void Particle::checkCollision(std::vector<Particle>* particles, Cube boundary, int index) {
	// Rebote con bordes + corrección de posición
	if (pos.x - radius < boundary.minX) {
		pos.x = boundary.minX + radius;
		speed.x *= -ENERGY_LOSS;
	}
	if (pos.x + radius > boundary.maxX) {
		pos.x = boundary.maxX - radius;
		speed.x *= -ENERGY_LOSS;
	}

	if (pos.y - radius < boundary.minY) {
		pos.y = boundary.minY + radius;
		speed.y *= -ENERGY_LOSS;
	}
	if (pos.y + radius > boundary.maxY) {
		pos.y = boundary.maxY - radius;
		speed.y *= -ENERGY_LOSS;
	}
	if (pos.z - radius < boundary.minZ) {
		pos.z = boundary.minZ + radius;
		speed.z *= -ENERGY_LOSS;
	}
	if (pos.z + radius > boundary.maxZ) {
		pos.z = boundary.maxZ - radius;
		speed.z *= -ENERGY_LOSS;
	}

	for (int j = index + 1; j < particles->size(); j++) {
		Particle& other = (*particles)[j];

		physicsSolver.solveGravity(*this, other);

		physicsSolver.solveCollition(*this, other);
	}
}
