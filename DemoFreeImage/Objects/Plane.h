#pragma once
#include "Object3d.h"
#include "../Maths/Vector3d.h"
#include "../Render/Ray.h"

class Plane : public Object3d
{
private:
	Vector3d normal;

public:
	Plane() = default;
	Plane(Material material, Vector3d position, Vector3d normal);
	Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface);
	Vector3d getNormal();
	std::pair<bool, Vector3d> doesRayIntersect(Ray ray);

	Color getColor();
};

