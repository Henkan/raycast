#pragma once
#include <utility>
#include "../Maths/Vector3d.h"
#include "../Render/Ray.h"
#include <vector>
#include "../Objects/Plane.h"
class Camera
{
private:
	double focal;
	Vector3d position;
	Vector3d direction;
	Plane nearPlane;
	Plane farPlane;
	double nearDistance;
	double farDistance;
	double imageSize;
	std::pair<int, int> resolution;

	void initializePlanes();
public:
	Camera() = default;
	Camera(Vector3d position, Vector3d direction, double focal, double nearDistance, double farDistance, double imageSize, std::pair<int, int> resolution);
	std::pair<Object3d*, Vector3d> sendRay(Ray ray, std::vector<Object3d*> objects);
	Vector3d getPosition();
	Vector3d getDirection();
	std::pair<int, int> getResolution();
	double getImageSize();
	double getFocal();
	
};

