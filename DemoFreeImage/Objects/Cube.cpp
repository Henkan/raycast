#include "Cube.h"

Cube::Cube(Vector3d position, std::vector<Vector3d> vertices, std::vector<Triangle> triangles) : Object3d(position), vertices(vertices), triangles(triangles){}
double Cube::getVolume() {
	return 0;
}