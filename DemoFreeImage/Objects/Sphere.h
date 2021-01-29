#pragma once

#include "Object3d.h"

class Sphere: public Object3d
{
private :
	double radius;
	Sphere();
public :
	Sphere(Material material, Vector3d center, double radius);
	double getRadius();
	Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface);

};

