#include "LightSource.h"

LightSource::LightSource(Vector3d position) : position(position), color(Color(255,255,255)), intensity(1){}

Color LightSource::getColor()
{
	return color;
}

Vector3d LightSource::getPosition()
{
	return position;
}

double LightSource::getIntensity()
{
	return intensity;
}
