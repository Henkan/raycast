#pragma once

#include "Object3d.h"

class Sphere: public Object3d
{
private :
	double radius;
	Sphere();
public :
	Sphere(Vector3d center, double radius, std::map<char,int> color);
	double getRadius();
	double getVolume();

};

