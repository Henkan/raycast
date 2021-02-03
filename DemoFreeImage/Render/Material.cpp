#include "Material.h"

Material::Material() {}

Material::Material(Color color, double diffuse, double ambient, double specular, double shininess) : color(color), diffuse(diffuse), ambient(ambient), specular(specular), shininess(shininess) {}

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

double Material::getShininess() {
	return shininess;
}