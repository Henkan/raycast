#pragma once
#include "../Maths/Vector3d.h"

class Object3d
{
private :
	Vector3d position;
	

public :
	Object3d(Vector3d position);
	Vector3d getPosition();
	virtual double getVolume() = 0;

};

