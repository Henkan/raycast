#include "Vector3d.h"
#include <math.h>
#include <iostream>

Vector3d::Vector3d() : x(0), y(0), z(0) {}

Vector3d::Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3d::Vector3d(std::string x, std::string y, std::string z) : x(std::stoi(x)), y(std::stoi(y)), z(std::stoi(z)){}

Vector3d::Vector3d(const Vector3d& other) : x(other.x), y(other.y), z(other.z) {}

void Vector3d::normalize() {
	double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x /= length;
	y /= length;
	z /= length;
}

double Vector3d::dotProduct(const Vector3d& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

Vector3d Vector3d::crossProduct(const Vector3d& other)
{
	double newX = y * other.z - z * other.y;
	double newY = -x * other.z + z * other.x;
	double newZ = x * other.y - y * other.x;
	return Vector3d(newX, newY, newZ);
}

Vector3d Vector3d::getDirection(const Vector3d& end)
{
	return Vector3d(end.x - x, end.y - y, end.z - z);
}

Vector3d Vector3d::getReflected(Vector3d& normal)
{
	//lumiere R = 2N(N.L)-L
	double scal = normal.dotProduct(*this);
	Vector3d temp = normal * (scal * 2);
	return (temp - *this);
}

double Vector3d::getLength()
{
	return sqrt(dotProduct(*this));
}

double Vector3d::getNorm()
{
	return sqrt(dotProduct(*this));
}

double Vector3d::getX()
{
	return x;
}

double Vector3d::getY()
{
	return y;
}

double Vector3d::getZ()
{
	return z;
}

void Vector3d::print()
{
	std::cout << x << " " << y << " " << z << "\n";
}

Vector3d Vector3d::operator+(const Vector3d& other) {
	return Vector3d(x + other.x, y + other.y, z + other.z);
}

Vector3d& Vector3d::operator+=(const Vector3d& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3d Vector3d::operator-(const Vector3d& other)
{
	return Vector3d(x - other.x, y - other.y, z - other.z);
}

Vector3d Vector3d::operator*(double coefficient)
{
	return Vector3d(x * coefficient, y*coefficient, z*coefficient);
}

Vector3d Vector3d::operator/(double coefficient)
{
	return Vector3d(x / coefficient, y / coefficient, z / coefficient);
}
