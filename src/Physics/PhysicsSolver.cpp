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