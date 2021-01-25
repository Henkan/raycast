#include "Scene.h"

Scene::Scene(Vector3d origin) : origin(origin), objects(std::vector<Object3d*>()) {}

void Scene::addObject(Object3d* object)
{
	objects.push_back(object);
}
