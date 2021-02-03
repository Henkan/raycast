#pragma once
#include "../Maths/Vector3d.h"
#include "Color.h"
class LightSource
{
private:
	Vector3d position;
	Color color;
public:
	LightSource();
	LightSource(Vector3d position);
	LightSource(Vector3d position, Color color);
	Color getColor();
	Vector3d getPosition();
};

