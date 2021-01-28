#include "Object3d.h"

Object3d::Object3d(Vector3d position, std::map<char,int> color) : position(position), color(color) {}

Vector3d Object3d::getPosition()
{
	return position;
}

std::map<char, int> Object3d::getColor()
{
	return color;
}
