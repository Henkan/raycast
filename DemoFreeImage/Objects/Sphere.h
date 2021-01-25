#pragma once

#include "Object3d.h"

class Sphere: public Object3d
{
private :
	Vector3d center;
	float radius;
	Sphere();
public :
	Sphere(Vector3d center, Vector3d radius);
	double getVolume();

};

