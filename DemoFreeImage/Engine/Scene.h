#pragma once
#include "../Maths/Vector3d.h"
#include "../Objects/Object3d.h"
#include "../Render/Camera.h"
#include <vector>
#include "../Render/LightSource.h"

class Scene
{
private:
	Camera camera;
	std::vector<Object3d*> objects;
	std::vector<LightSource*> lightSources;

public:
	Scene();
	Scene(Camera camera);

	void addCamera(Camera camera);
	Camera getCamera();
	void addObject(Object3d* object);
	void addObjects(std::vector<Object3d*> listObjects);
	void addLightSource(LightSource* lightSource);
	void addLightSources(std::vector<LightSource*> lightSourcesToAdd);
	void render();

	void printObjects();
	void printLight();

	~Scene();
};

