#include "Particle.hpp"

#include "../../include/lib.h"

void Particle::applyForce(Vector3 force, float dt) {
	speed += Vector3Scale(force, dt);

	if (Vector3Length(speed) > maxSpeed)
		speed = Vector3Scale(Vector3Normalize(speed), maxSpeed);
}

void Particle::update(float dt) {
	speed = Vector3Add(speed, Vector3Scale(acceleration, dt));
	pos = Vector3Add(pos, Vector3Scale(speed, dt));
	acceleration = Vector3Zero();  // Reset para el próximo frame
}

void Particle::draw() {
	DrawSphereWires(pos, radius, 10, 10, color);
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

		solveCollition(other);
	}
}

void Particle::solveCollition(Particle& other) {
	auto impactVector = Vector3Normalize(Vector3Subtract(other.pos, this->pos));
	auto distance = Vector3Distance(this->pos, other.pos);
	auto minDistance = this->radius + other.radius;

	if (distance < this->radius + other.radius) {
		auto normal = Vector3Normalize(Vector3Subtract(other.pos, this->pos));
		auto overlap = (this->radius + other.radius) - Vector3Distance(this->pos, other.pos);

		this->pos -= normal * (overlap / 2);
		other.pos += normal * (overlap / 2);

		auto mSum = this->mass + other.mass;
		auto relativeVel = Vector3Subtract(other.speed, this->speed);
		auto num = Vector3DotProduct(relativeVel, impactVector);
		auto den = mSum * distance * distance;
		auto deltaVA = impactVector;

		deltaVA = Vector3Scale(deltaVA, 2 * other.mass * num / den);
		this->speed += deltaVA;

		auto deltaVB = impactVector;
		deltaVB = Vector3Scale(deltaVB, -2 * this->mass * num / den);
		other.speed += deltaVB;
	}
}