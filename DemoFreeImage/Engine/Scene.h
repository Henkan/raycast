#pragma once
#include "../Maths/Vector3d.h"
#include "../Objects/Object3d.h"
#include "../Render/Camera.h"
#include <vector>
#include "../Render/LightSource.h"

class Scene
{
private:
	Vector3d origin;
	Camera camera;
	std::vector<Object3d*> objects;
	std::vector<LightSource*> lightSources;

public:
	Scene();
	Scene(Vector3d origin, Camera camera);
	void addObject(Object3d* object);
	void addLightSource(LightSource* lightSource);
	void render();
};

