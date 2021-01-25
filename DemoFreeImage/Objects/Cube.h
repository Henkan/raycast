#pragma once
#include "Object3d.h"
#include <vector>

class Cube: public Object3d
{
private:
	std::vector<Vector3d> vertices; 
	Cube();

public:
	Cube(std::vector<Vector3d> vertices);

};

