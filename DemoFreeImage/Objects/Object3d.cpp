#include "Object3d.h"

Object3d::Object3d(Vector3d position) : position(position) {}

Vector3d Object3d::getPosition()
{
	return position;
}
