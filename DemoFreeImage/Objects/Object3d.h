#pragma once
#include "../Maths/Vector3d.h"
#include <map>
class Object3d
{
private :
	Vector3d position;
	std::map<char, int> color;
	

public :
	Object3d(Vector3d position, std::map<char, int> color);
	Vector3d getPosition();
	std::map<char, int> getColor();
	virtual double getVolume() = 0;

};

