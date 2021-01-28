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
	Cube(Vector3d position, std::vector<Vector3d> vertices, std::vector<Triangle> triangles, std::map<char, int> color);
	double getVolume();
};

