#include "Object3d.h"

Object3d::Object3d(Material material, Vector3d position) : material(material),position(position) {}

Vector3d Object3d::getPosition()
{
	return position;
}

Material Object3d::getMaterial()
{
	return material;
}
