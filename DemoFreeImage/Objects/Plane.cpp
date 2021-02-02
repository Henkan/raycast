#include "Plane.h"
#include <iostream>

Plane::Plane(){}

Plane::Plane(Material material, Vector3d position, Vector3d normal) : Object3d(material, position) {
	this->normal = normal;
	this->normal.normalize();
}

Vector3d Plane::getNormalVectorOfSurface(Vector3d positionOnSurface)
{
	return normal ;
}

Vector3d Plane::getNormal()
{
	return normal;
}

std::pair<bool, Vector3d> Plane::doesRayIntersect(Ray ray)
{
	Vector3d rayPos = ray.getPosition();
	Vector3d rayDir = ray.getDirection();

	double denominator = normal.dotProduct(rayDir);
	if (abs(denominator) > 0.00001) { //Ray is not parallel to the plane
		double t = (position - rayPos).dotProduct(normal) / denominator ;
		if (t >= 0) {
			Vector3d intersection(rayPos.getX() + t * rayDir.getX(), rayPos.getY() + t * rayDir.getY(), rayPos.getZ() + t * rayDir.getZ());
			return std::pair<bool, Vector3d>(true, intersection);
		}
	}

	return std::pair<bool, Vector3d>(false, Vector3d());
}
