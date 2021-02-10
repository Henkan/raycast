#include "Triangle.h"
#include <iostream>

Triangle::Triangle(Material material, std::array<Vector3d, 3> vertices): Object3d(material, vertices[0]), vertices(vertices)
{
	Vector3d AB = vertices[1] - vertices[0];
	Vector3d CA = vertices[0] - vertices[2];
	normal = AB.crossProduct(CA);
	normal.normalize();

}

Vector3d Triangle::getNormal()
{
	return normal;
}

Vector3d Triangle::getNormalVectorOfSurface(Vector3d positionOnSurface)
{
	return normal;
}


std::pair<bool, Vector3d> Triangle::doesRayIntersect(Ray ray)
{
	Vector3d rayPos = ray.getPosition();
	Vector3d rayDir = ray.getDirection();
	Vector3d intersection;

	//Get the normal facing towards the ray hence the camera to see the actual color
	if ((normal.getZ() < 0) == (rayDir.getZ() < 0)) {
		normal = normal * -1;
	}

	double denominator = normal.dotProduct(rayDir);
	if (abs(denominator) > 0.00001) { //Ray is not parallel to the plane
		double t = (position - rayPos).dotProduct(normal) / denominator;
		if (t >= 0) {
			intersection = Vector3d(rayPos.getX() + t * rayDir.getX(), rayPos.getY() + t * rayDir.getY(), rayPos.getZ() + t * rayDir.getZ());
		}
		else {
			return std::pair<bool, Vector3d>(false, Vector3d());
		}
	}
	else {
		return std::pair<bool, Vector3d>(false, Vector3d());
	}

	
	Vector3d AB = vertices[1] - vertices[0];
	Vector3d AC = vertices[2] - vertices[1];
	double aireABC = (1.0 / 2) * (AB.crossProduct(AC)).getNorm();

	Vector3d IA = vertices[0] - intersection;
	
	Vector3d IB = vertices[1] - intersection;
	Vector3d IC = vertices[2] - intersection;
	double aireIAB = (1.0 / 2) * (IA.crossProduct(IB)).getNorm();
	double aireIAC = (1.0 / 2) * (IA.crossProduct(IC)).getNorm();
	double aireIBC = (1.0 / 2) * (IB.crossProduct(IC)).getNorm();

	if (abs((aireIAB + aireIAC + aireIBC) - aireABC) < 0.01) {
		return std::pair<bool, Vector3d>(true, intersection);
	}
	else {
		return std::pair<bool, Vector3d>(false, Vector3d());
	}
}

Color Triangle::getColor()
{
	return material.getColor();
}
