#pragma once
#include <array>
#include "../Maths/Vector3d.h"
#include "../Render/Ray.h"
#include "../Render/Color.h"
#include "Object3d.h"

class Triangle : public Object3d
{
private:
	std::array<Vector3d, 3> vertices;
	Vector3d normal;

public:
	Triangle();
	Triangle(Material material, std::array<Vector3d,3> vertices);
	Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface);
	Vector3d getNormal();
	std::pair<bool, Vector3d> doesRayIntersect(Ray ray);

	Color getColor();
};

