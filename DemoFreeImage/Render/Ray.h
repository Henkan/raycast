#pragma once
#include "../Maths/Vector3d.h"
#include "../Objects/Object3d.h"
class Ray
{
private :
	Vector3d position;
	Vector3d direction;
	Ray();
public :
	Ray(Vector3d position, Vector3d direction);
	bool collides(Object3d* object);
};

