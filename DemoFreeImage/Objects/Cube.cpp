#include "Cube.h"

Cube::Cube(Vector3d position, std::vector<Vector3d> vertices, std::vector<Triangle> triangles, std::map<char, int> color) : Object3d(position, color), vertices(vertices), triangles(triangles){}
double Cube::getVolume() {
	return 0;
}