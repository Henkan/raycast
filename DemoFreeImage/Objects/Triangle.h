#pragma once
#include <array>
#include "../Maths/Vector3d.h"

class Triangle
{
private:
	std::array < int,3 > vertices; //index 
	std::array<int, 3> textures;
	std::array<int, 3> normal;

public:
	Triangle();
	Triangle(std::array<int,3> vertices);
};

