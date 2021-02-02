#include "Material.h"

Material::Material() {}

Material::Material(Color color, double diffuse, double ambient, double specular) : color(color), diffuse(diffuse), ambient(ambient), specular(specular){}

Color Material::getColor()
{
	return color;
}

double Material::getDiffuse()
{
	return diffuse;
}

double Material::getAmbient()
{
	return ambient;
}

double Material::getSpecular()
{
	return specular;
}
