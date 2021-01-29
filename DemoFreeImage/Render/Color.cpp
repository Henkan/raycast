#include "Color.h"

Color::Color(){}

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