#include "Color.h"
#include <iostream>

Color::Color() : red(0), green(0), blue(0) {}

Color::Color(int red, int green, int blue): red(red), green(green), blue(blue) {}

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

void Color::print() {
	std::cout << red << " " << green << " " << blue << "\n";
}