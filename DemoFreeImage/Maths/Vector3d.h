#pragma once
class Vector3d
{
private:
	double x;
	double y;
	double z;
public:
	Vector3d();
	Vector3d(double x, double y, double z);
	Vector3d(const Vector3d& other);

	void normalize();
	double dotProduct(const Vector3d& other);
	Vector3d crossProduct(const Vector3d& other);
	Vector3d getDirection(const Vector3d& end);
	double getLength();
	double getX();
	double getY();
	double getZ();

	void print();

	Vector3d operator+(const Vector3d& other);
	Vector3d& operator+=(const Vector3d& other);
	Vector3d operator-(const Vector3d& other);
	Vector3d operator*(double coefficient);
};

