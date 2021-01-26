#include "Camera.h"
#include <iostream>

Camera::Camera()
{
	focal = 1;
	position = Vector3d(0, 0, -1);
	direction = Vector3d(0, 0, 1);
	nearDistance = 0.5;
	farDistance = 5;
	imageSize = 10;
	resolution = std::pair<int, int>(600, 400);
}

bool Camera::sendRay(Ray ray, std::vector<Object3d*> objects)
{

	for (auto it = objects.begin(); it != objects.end(); ++it) {
		if (ray.collides(*it)) {
			return true;
		}
		
	}
	return false;
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

