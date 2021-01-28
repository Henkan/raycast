#include "Sphere.h"

Sphere::Sphere(Vector3d center, double radius, std::map<char,int> color) : Object3d(center, color), radius(radius){}

double Sphere::getRadius()
{
	return radius;
}

double Sphere::getVolume() {
	return 0;
}