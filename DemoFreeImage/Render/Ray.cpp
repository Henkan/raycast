#include "Ray.h"
#include <cmath>
#include "../Objects/Sphere.h"
#include <iostream>

Ray::Ray(Vector3d position, Vector3d direction) : position(position), direction(direction){}

std::pair<bool, Vector3d> Ray::collides(Object3d* object)
{
	return object->doesRayIntersect(*this);
}

Vector3d Ray::getPosition()
{
	return position;
}

Vector3d Ray::getDirection()
{
	return direction;
}
