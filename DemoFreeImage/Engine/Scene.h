#pragma once
#include "../Maths/Vector3d.h"
#include "../Objects/Object3d.h"
#include <vector>

class Scene
{
private:
	Vector3d origin;
	std::vector<Object3d*> objects;
	Scene();
public:
	Scene(Vector3d origin);
	void addObject(Object3d* object);
};

