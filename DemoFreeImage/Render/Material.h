#pragma once
#include "Color.h"
#include "../Render/LightSource.h"
class Material
{
private :
	Color color;
	double diffuse;
	double ambient;
	double specular;
	double shininess;

public :
	Material();
	Material(Color color, double diffuse, double ambient, double specular, double shininess);
	Color getColor();
	double getDiffuse();
	double getAmbient();
	double getSpecular();
	double getShininess();
	Color computeAmbient();
	Color computeDiffuse(LightSource light, double attenuation, double dotProductResult);
	Color computeSpecular(LightSource light, double attenuation, double dotProductResult);
};

