#pragma once

class Particle;

class PhysicsSolver {
   public:
	PhysicsSolver() {};

	void solveGravity(Particle& self, Particle& other);
	void solveCollition(Particle& self, Particle& other);
};