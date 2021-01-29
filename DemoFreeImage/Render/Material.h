#pragma once
#include "Color.h"
class Material
{
private :
	Color color;
	double diffuse;
	double ambient;
	double specular;
	Material();

public :
	Material(Color color, double diffuse, double ambient, double specular);
	Color getColor();
	double getDiffuse();
	double getAmbient();
	double getSpecular();
};

