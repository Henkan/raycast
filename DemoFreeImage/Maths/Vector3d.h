#pragma once
#include <string>

class Vector3d
{
private:
	double x;
	double y;
	double z;
public:
	Vector3d();
	Vector3d(double x, double y, double z);
	Vector3d(std::string x, std::string y, std::string z);
	Vector3d(const Vector3d& other);

	void normalize();
	double dotProduct(const Vector3d& other) const;
	Vector3d crossProduct(const Vector3d& other);
	Vector3d getDirection(const Vector3d& end);
	Vector3d getReflected(Vector3d& normal);
	double getLength();
	double getNorm();
	double getX();
	double getY();
	double getZ();

	void print();

	Vector3d operator+(const Vector3d& other);
	Vector3d& operator+=(const Vector3d& other);
	Vector3d operator-(const Vector3d& other);
	Vector3d operator*(double coefficient);
	Vector3d operator/(double coefficient);
};

