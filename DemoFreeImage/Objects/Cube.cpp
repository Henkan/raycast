#include "Cube.h"

Cube::Cube(std::vector<Vector3d> vertices, std::vector<Triangle> triangles) : Object3d(), vertices(vertices), triangles(triangles){}
double Cube::getVolume() {
	return 0;
}