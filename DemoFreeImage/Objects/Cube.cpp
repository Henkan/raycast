#include "Cube.h"

Cube::Cube(Material material, Vector3d position, std::vector<Vector3d> vertices, std::vector<Triangle> triangles) : Object3d(material, position), vertices(vertices), triangles(triangles){}
double Cube::getVolume() {
	return 0;
}
Vector3d Cube::getNormalVectorOfSurface(Vector3d positionOnSurface)
{
	return Vector3d();
}

std::pair<bool, Vector3d> Cube::doesRayIntersect(Ray ray)
{
	return std::pair<bool, Vector3d>();
}