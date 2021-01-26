#include "Sphere.h"

Sphere::Sphere(Vector3d center, double radius) : Object3d(center), radius(radius){}

double Sphere::getRadius()
{
	return radius;
}

double Sphere::getVolume() {
	return 0;
}