#pragma once
#include "Object3d.h"
#include "Triangle.h"
#include <vector>

class Cube: public Object3d
{
private:
	std::vector<Vector3d> vertices; 
	std::vector<Triangle> triangles;
	Cube();

public:
	Cube(std::vector<Vector3d> vertices, std::vector<Triangle> triangles);
	double getVolume();
};

