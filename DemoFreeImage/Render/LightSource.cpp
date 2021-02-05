#include "LightSource.h"

LightSource::LightSource()
{
}

LightSource::LightSource(Vector3d position) : position(position), color(Color(255,255,255)) {}

LightSource::LightSource(Vector3d position, Color color) : position(position), color(color) {}


Color LightSource::getColor()
{
	return color;
}

Vector3d LightSource::getPosition()
{
	return position;
}

LightSource::~LightSource()
{
}
