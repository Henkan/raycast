#pragma once
#include "../Maths/Vector3d.h"
#include "Color.h"
class LightSource
{
private:
	Vector3d position;
	Color color;
	double intensity;
	LightSource();

public:
	LightSource(Vector3d position);
	Color getColor();
	Vector3d getPosition();
	double getIntensity();

};

