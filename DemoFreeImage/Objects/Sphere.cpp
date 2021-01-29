#include "Sphere.h"

Sphere::Sphere(Material material, Vector3d center, double radius) : Object3d(material, center), radius(radius){}

double Sphere::getRadius()
{
	return radius;
}

Vector3d Sphere::getNormalVectorOfSurface(Vector3d positionOnSurface) {
	Vector3d norm = position.getDirection(positionOnSurface);
	norm.normalize();
	return norm;
}