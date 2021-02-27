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
	double reflectivity;

public :
	Material() = default;
	Material(Color color, double diffuse, double ambient, double specular, double shininess, double reflectivity);
	Color getColor();
	double getDiffuse();
	double getAmbient();
	double getSpecular();
	double getShininess();
	double getReflectivity();
	Color computeAmbient();
	Color computeDiffuse(LightSource light, double attenuation, double dotProductResult);
	Color computeSpecular(LightSource light, double attenuation, double dotProductResult);
};

