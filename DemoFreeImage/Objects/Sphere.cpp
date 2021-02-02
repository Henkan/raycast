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

std::pair<bool, Vector3d> Sphere::doesRayIntersect(Ray ray)
{

	Vector3d rayPos = ray.getPosition();
	Vector3d rayDir = ray.getDirection();

	//Intersection avec une sphere
	Vector3d V0(rayPos.getX() - position.getX(), rayPos.getY() - position.getY(), rayPos.getZ() - position.getZ());

	double coefA = rayDir.dotProduct(rayDir);
	double coefB = 2 * (V0.getX() * rayDir.getX() + V0.getY() * rayDir.getY() + V0.getZ() * rayDir.getZ());
	double coefC = pow(V0.getX(), 2) + pow(V0.getY(), 2) + pow(V0.getZ(), 2) - pow(radius, 2);

	double determinant = pow(coefB, 2) - 4 * coefA * coefC;
	if (determinant > 0) { //There is an intersection
		double t1 = (-coefB - sqrt(determinant)) / (2 * coefA);
		double t2 = (-coefB + sqrt(determinant)) / (2 * coefA);

		Vector3d intersection1(rayPos.getX() + t1 * rayDir.getX(), rayPos.getY() + t1 * rayDir.getY(), rayPos.getZ() + t1 * rayDir.getZ());
		Vector3d intersection2(rayPos.getX() + t2 * rayDir.getX(), rayPos.getY() + t2 * rayDir.getY(), rayPos.getZ() + t2 * rayDir.getZ());

		if (t1 < t2) {
			return std::pair<bool, Vector3d>(true, intersection1);
		}
		else {
			return std::pair<bool, Vector3d>(true, intersection2);
		}
	}
	else if (determinant == 0) { //Tangent
		double t = (-coefB) / (2 * coefA);
		Vector3d intersection(rayPos.getX() + t * rayDir.getX(), rayPos.getY() + t * rayDir.getY(), rayPos.getZ() + t * rayDir.getZ());
		return std::pair<bool, Vector3d>(true, intersection);
	}
	//No intersection
	return std::pair<bool, Vector3d>(false, Vector3d());
}
