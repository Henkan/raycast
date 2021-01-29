#pragma once
#include "../Maths/Vector3d.h"
#include <map>
#include "../Render/Material.h"
class Object3d
{
protected :
	Material material;
	Vector3d position;
	

public :
	Object3d(Material material, Vector3d position);
	Vector3d getPosition();
	Material getMaterial();
	virtual Vector3d getNormalVectorOfSurface(Vector3d positionOnSurface) = 0;

};

