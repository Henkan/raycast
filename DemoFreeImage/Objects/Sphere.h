#pragma once

#include "Object3d.h"
#include "../Render/Ray.h"

class Sphere: public Object3d
{
private :
	double radius;

public :
	Sphere();
	Sphere(Material material, Vector3d center, double radius);
	double getRadius();
	Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface);
	std::pair<bool, Vector3d> doesRayIntersect(Ray ray);

};

