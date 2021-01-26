#pragma once
#include "../Maths/Vector3d.h"
#include "../Objects/Object3d.h"
#include "../Render/Camera.h"
#include <vector>

class Scene
{
private:
	Vector3d origin;
	Camera camera;
	std::vector<Object3d*> objects;
	Scene();
public:
	Scene(Vector3d origin, Camera camera);
	void addObject(Object3d* object);
	void render();
};

