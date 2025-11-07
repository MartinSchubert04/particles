#pragma once
#include "../../include/lib.h"

class Cube {
   public:
	Vector3 position;
	Vector3 size;
	Color color;

	float minX;
	float maxX;
	float minY;
	float maxY;
	float minZ;
	float maxZ;

	// Constructor por defecto
	Cube() : position{0, 0, 0}, size{1, 1, 1}, color{WHITE} {}

	Cube(Vector3 position, Vector3 size, Color color) : position(position), size(size), color(color) {
		minX = position.x - size.x / 2;
		maxX = position.x + size.x / 2;
		minY = position.y - size.y / 2;
		maxY = position.y + size.y / 2;
		minZ = position.z - size.z / 2;
		maxZ = position.z + size.z / 2;
	}
};