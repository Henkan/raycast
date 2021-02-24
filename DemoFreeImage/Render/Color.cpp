#include "Color.h"
#include <iostream>

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(int red, int green, int blue): red(red), green(green), blue(blue) {}

Color::Color(std::string red, std::string green, std::string blue) : red(std::stoi(red)), green(std::stoi(green)), blue(std::stoi(blue)){}

int Color::getRed() {
	return red;
}

int Color::getGreen() {
	return green;
}

int Color::getBlue() {
	return blue;
}

Color Color::operator+(const Color& other) {
	return Color(red + other.red, green + other.green, blue + other.blue);
}

Color Color::operator+(int other)
{
	return Color(red + other, green + other, blue + other);
}

Color Color::operator*(double factor)
{
	return Color(red * factor, green * factor, blue * factor);
}

void Color::print() {
	std::cout << red << " " << green << " " << blue << "\n";
}

void Color::correctRange() {
	if (red < 0) red = 0;
	else if (red > 255) red = 255;
	if (green < 0) green = 0;
	else if (green > 255) green = 255;
	if (blue < 0) blue = 0;
	else if (blue > 255) blue = 255;
}