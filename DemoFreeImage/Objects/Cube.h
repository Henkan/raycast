#pragma once
#include "Object3d.h"
#include "Triangle.h"
#include <vector>
#include "../Render/Ray.h"

class Cube: public Object3d
{
private:
	std::vector<Vector3d> vertices; 
	std::vector<Triangle> triangles;

public:
	Cube();
	Cube(Material material, Vector3d position, std::vector<Vector3d> vertices, std::vector<Triangle> triangles);
	double getVolume();
	Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface);
	std::pair<bool, Vector3d> doesRayIntersect(Ray ray);
};

