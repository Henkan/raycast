#pragma once
#include <utility>
#include "../Maths/Vector3d.h"
#include "../Render/Ray.h"
#include <vector>
class Camera
{
private:
	double focal;
	Vector3d position;
	Vector3d direction;
	double nearDistance;
	double farDistance;
	double imageSize;
	std::pair<int, int> resolution;

public:
	Camera();
	bool sendRay(Ray ray, std::vector<Object3d*> objects);
	Vector3d getPosition();
	Vector3d getDirection();
	std::pair<int, int> getResolution();
	double getImageSize();
	double getFocal();
	
};

