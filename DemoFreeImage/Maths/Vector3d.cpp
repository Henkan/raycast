#include "Vector3d.h"
#include <math.h>

Vector3d::Vector3d() : x(0), y(0), z(0) {}

Vector3d::Vector3d(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3d::Vector3d(const Vector3d& other) : x(other.x), y(other.y), z(other.z) {}

void Vector3d::normalize() {
	double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x /= length;
	y /= length;
	z /= length;
}

double Vector3d::dotProduct(const Vector3d& other)
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
