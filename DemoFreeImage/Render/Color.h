#pragma once
class Color
{
private :
	int red;
	int green;
	int blue;


public :
	Color();
	Color(int red, int green, int blue);
	int getRed();
	int getBlue();
	int getGreen();
	void correctRange();
	Color operator+(const Color& other);
	Color operator+(int other);
	void print();
};

