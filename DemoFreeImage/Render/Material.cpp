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

Color Material::computeAmbient()
{
	return Color((int)(this->getColor().getRed() * this->ambient),
		(int)(this->getColor().getGreen() * ambient),
		(int)(this->getColor().getBlue() * ambient));
}

Color Material::computeDiffuse(LightSource light, double attenuation, double dotProductResult)
{
	return Color((int)(this->getColor().getRed() * this->diffuse * attenuation * light.getColor().getRed() * dotProductResult),
		(int)(this->getColor().getGreen() * this->getDiffuse() * attenuation * light.getColor().getGreen() * dotProductResult),
		(int)(this->getColor().getBlue() * this->getDiffuse() * attenuation * light.getColor().getBlue() * dotProductResult));
}

Color Material::computeSpecular(LightSource light, double attenuation, double dotProductResult)
{
	return Color((int)(75 * this->specular * attenuation * light.getColor().getRed() * pow(dotProductResult, this->shininess)),
		(int)(75 * this->specular * attenuation * light.getColor().getGreen() * pow(dotProductResult, this->shininess)),
		(int)(75 * this->specular * attenuation * light.getColor().getBlue() * pow(dotProductResult, this->shininess)));
}
