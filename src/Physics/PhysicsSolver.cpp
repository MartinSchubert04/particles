#include "PhysicsSolver.hpp"

#include "../../include/lib.h"
#include "Particle.hpp"

void PhysicsSolver::solveGravity(Particle& self, Particle& other) {
	Vector3 dir = Vector3Subtract(other.pos, self.pos);
	float distance = Vector3Length(dir);

	if (distance < 0.001f) return;
	dir = Vector3Normalize(dir);

	// Ley de gravitación universal: F = G * m1 * m2 / r²
	float forceMag = (G * self.mass * other.mass) / (distance * distance);

	// Aceleración que experimenta cada partícula
	Vector3 forceOnThis = Vector3Scale(dir, forceMag / self.mass);
	Vector3 forceOnOther = Vector3Scale(dir, -forceMag / other.mass);

	self.acceleration = Vector3Add(self.acceleration, forceOnThis);
	other.acceleration = Vector3Add(other.acceleration, forceOnOther);
}

void PhysicsSolver::solveCollition(Particle& self, Particle& other) {
	auto impactVector = Vector3Normalize(Vector3Subtract(other.pos, self.pos));
	auto distance = Vector3Distance(self.pos, other.pos);
	auto minDistance = self.radius + other.radius;

	if (distance < self.radius + other.radius) {
		auto normal = Vector3Normalize(Vector3Subtract(other.pos, self.pos));
		auto overlap = (self.radius + other.radius) - Vector3Distance(self.pos, other.pos);

		self.pos -= normal * (overlap / 2);
		other.pos += normal * (overlap / 2);

		auto mSum = self.mass + other.mass;
		auto relativeVel = Vector3Subtract(other.speed, self.speed);
		auto num = Vector3DotProduct(relativeVel, impactVector);
		auto den = mSum * distance * distance;
		auto deltaVA = impactVector;

		deltaVA = Vector3Scale(deltaVA, 2 * other.mass * num / den);
		self.speed += deltaVA;

		auto deltaVB = impactVector;
		deltaVB = Vector3Scale(deltaVB, -2 * self.mass * num / den);
		other.speed += deltaVB;
	}
}