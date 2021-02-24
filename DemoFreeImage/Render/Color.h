#pragma once
#include <string>
class Color
{
private :
	int red;
	int green;
	int blue;


public :
	Color();
	Color(int red, int green, int blue);
	Color(std::string red, std::string green, std::string blue);
	int getRed();
	int getBlue();
	int getGreen();
	void correctRange();
	Color operator+(const Color& other);
	Color operator+(int other);
	Color operator*(double factor);
	void print();
};

