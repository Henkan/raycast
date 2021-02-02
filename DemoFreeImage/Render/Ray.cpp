#include "Ray.h"
#include <cmath>
#include "../Objects/Sphere.h"
#include <iostream>

Ray::Ray(Vector3d position, Vector3d direction) : position(position), direction(direction){}

std::pair<bool, Vector3d> Ray::collides(Object3d* object)
{
	//TODO: check which object is nearer if multiple collisions
	return object->doesRayIntersect(*this);
	/*//Intersection avec une sphere
	Vector3d V0(position.getX() - object->getPosition().getX(), position.getY() - object->getPosition().getY(), position.getZ() - object->getPosition().getZ());

	double coefA = direction.dotProduct(direction);
	double coefB = 2 * (V0.getX() * direction.getX() + V0.getY() * direction.getY() + V0.getZ() * direction.getZ()) ;
	double coefC = pow(V0.getX(),2) + pow(V0.getY(), 2) + pow(V0.getZ(), 2) - pow(dynamic_cast<Sphere*>(object)->getRadius(),2);

	double determinant = pow (coefB, 2) - 4 * coefA * coefC;
	if (determinant > 0) { //There is an intersection
		double t1 = (-coefB - sqrt(determinant)) / (2 * coefA);
		double t2 = (-coefB + sqrt(determinant)) / (2 * coefA);

		Vector3d intersection1(position.getX() + t1 * direction.getX(), position.getY() + t1 * direction.getY(), position.getZ() + t1 * direction.getZ());
		Vector3d intersection2(position.getX() + t2 * direction.getX(), position.getY() + t2 * direction.getY(), position.getZ() + t2 * direction.getZ());

		if(t1 < t2){
			return std::pair<bool, Vector3d>(true, intersection1);
		}
		else {
			return std::pair<bool, Vector3d>(true, intersection2);
		}
	}
	else if (determinant == 0) { //Tangent
		double t = (-coefB) / (2 * coefA); 
		Vector3d intersection(position.getX() + t * direction.getX(), position.getY() + t * direction.getY(), position.getZ() + t * direction.getZ());
		return std::pair<bool, Vector3d>(true, intersection);
	}
	//No intersection
	return std::pair<bool, Vector3d>(false, Vector3d()); 
	*/
}

Vector3d Ray::getPosition()
{
	return position;
}

Vector3d Ray::getDirection()
{
	return direction;
}
