#pragma once
#include "../Maths/Vector3d.h"
//#include "../Objects/Object3d.h"

#include <utility>
class Object3d;

class Ray
{
private :
	Vector3d position;
	Vector3d direction;

public :
	Ray();
	Ray(Vector3d position, Vector3d direction);
	std::pair<bool, Vector3d> collides(Object3d* object);
	Vector3d getPosition();
	Vector3d getDirection();
};

