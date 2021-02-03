#include "Camera.h"
#include <iostream>

void Camera::initializePlanes()
{
	Vector3d farPoint = position + direction * farDistance;
	Vector3d farNormal = farPoint.getDirection(position);
	farNormal.normalize();
	farPlane = Plane(Material(Color(0, 0, 0), 0, 0, 0, 0), farPoint, farNormal);

	Vector3d nearPoint = position + direction * nearDistance;
	Vector3d nearNormal = position.getDirection(nearPoint);
	nearNormal.normalize();
	nearPlane = Plane(Material(Color(0, 0, 0), 0, 0, 0, 0), nearPoint, nearNormal);
}

Camera::Camera()
{
	focal = 1;
	position = Vector3d(0, 0, 0);
	direction = Vector3d(0, 0, 1);
	nearDistance = 0.5;
	farDistance = 100;
	imageSize = 2;
	resolution = std::pair<int, int>(640, 480);

	initializePlanes();
}

Camera::Camera(Vector3d position, Vector3d direction, double focal, double nearDistance, double farDistance, double imageSize, std::pair<int, int> resolution)
	: position(position), direction(direction), focal(focal), nearDistance(nearDistance), farDistance(farDistance), imageSize(imageSize), resolution(resolution)
{
	initializePlanes();
}

std::pair<Object3d*, Vector3d> Camera::sendRay(Ray ray, std::vector<Object3d*> objects)
{
	std::vector<std::pair<Object3d*,Vector3d>> objectsWithCollision;
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		std::pair<bool, Vector3d> result = ray.collides(*it);


		if (result.first) { //If collision
			double distanceCamCollision = position.getDirection(result.second).getLength();
			
			Vector3d farToCol = result.second - farPlane.getPosition();
			double distanceFarCol = farToCol.dotProduct(farPlane.getNormal());

			Vector3d nearToCol = result.second - nearPlane.getPosition();
			double distanceNearCol = nearToCol.dotProduct(nearPlane.getNormal());

			if (distanceNearCol >= 0 && distanceFarCol >= 0) { //Object in sight

				if (objectsWithCollision.empty()) { //Meaning there are no collision yet
					objectsWithCollision.push_back(std::pair<Object3d*, Vector3d>(*it, result.second));
				}
				else {
					double distanceCamOtherObject = position.getDirection(objectsWithCollision[0].second).getLength();
					if (distanceCamCollision < distanceCamOtherObject) { //New object is nearer
						objectsWithCollision.clear();
						objectsWithCollision.push_back(std::pair<Object3d*, Vector3d>(*it, result.second));
					}
				}
				
			}
		}
	}

	if (objectsWithCollision.empty()) {
		return std::pair<Object3d*, Vector3d>(nullptr,Vector3d());
	}
	else {
		return objectsWithCollision[0];
	}
	
}

Vector3d Camera::getPosition()
{
	return position;
}

Vector3d Camera::getDirection()
{
	return direction;
}

std::pair<int, int> Camera::getResolution()
{
	return resolution;
}

double Camera::getImageSize()
{
	return imageSize;
}

double Camera::getFocal()
{
	return focal;
}

