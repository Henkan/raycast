#include "Ray.h"
#include <cmath>
#include "../Objects/Sphere.h"
#include <iostream>

Ray::Ray(Vector3d position, Vector3d direction) : position(position), direction(direction){}

bool Ray::collides(Object3d* object)
{
	//Intersection avec une sphere
	Vector3d V0(position.getX() - object->getPosition().getX(), position.getY() - object->getPosition().getY(), position.getZ() - object->getPosition().getZ());

	double coefA = direction.dotProduct(direction);
	double coefB = 2 * (V0.getX() * direction.getX() + V0.getY() * direction.getY() + V0.getZ() * direction.getZ()) ;
	double coefC = pow(V0.getX(),2) + pow(V0.getY(), 2) + pow(V0.getZ(), 2) - pow(dynamic_cast<Sphere*>(object)->getRadius(),2);

	double determinant = pow (coefB, 2) - 4 * coefA * coefC;
	if (determinant > 0) {
		double t1 = (-coefB - sqrt(determinant)) / (2 * coefA);
		double t2 = (-coefB + sqrt(determinant)) / (2 * coefA);
		//std::cout << "\nt1 " << t1 << " t2 " << t2 << "\n";
		Vector3d intersection1(position.getX() + t1 * direction.getX(), position.getY() + t1 * direction.getY(), position.getZ() + t1 * direction.getZ());
		Vector3d intersection2(position.getX() + t2 * direction.getX(), position.getY() + t2 * direction.getY(), position.getZ() + t2 * direction.getZ());
		/*std::cout << "intersection 1 : ";
		intersection1.print();
		std::cout << "distance 1 : ";
		std::cout << position.getDirection(intersection1).getLength();
		std::cout << "\nintersection 2 : ";
		intersection2.print();
		std::cout << "distance 2 : ";
		std::cout <<position.getDirection(intersection2).getLength();*/
	}
	return (determinant > 0); 
}
