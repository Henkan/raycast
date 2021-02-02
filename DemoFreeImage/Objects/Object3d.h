#pragma once
#include "../Maths/Vector3d.h"
#include "../Render/Material.h"
#include "../Render/Ray.h"

#include <utility>

class Object3d
{
protected :
	Material material;
	Vector3d position;


public :
	Object3d();
	Object3d(Material material, Vector3d position);
	Vector3d getPosition();
	Material getMaterial();
	virtual Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface) = 0;
	virtual std::pair<bool, Vector3d> doesRayIntersect(Ray ray) = 0;


};

