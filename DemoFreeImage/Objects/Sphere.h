#pragma once

#include "Object3d.h"

class Sphere: public Object3d
{
private :
	double radius;
	Sphere();
public :
	Sphere(Vector3d center, double radius);
	double getRadius();
	double getVolume();

};

