#include <iostream>
#include "FreeImage.h"
#include "Engine/Scene.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"

/*
math
 - Vector3d
 - Matrix
render
 - Material
 - Camera
 - LightSource
 - Ray
objects
 - Object3d
 - Object2d ?
 - Sphere
 - Cube (cube et rectangle et trucs)
 - ... formes à implémenter
image + parser
 - Parser
engine
 - Engine
 - Scene

Classes: PascalCase
Fonctions: camelCase
Membres: camelCase, pas de _
*/

int main(int argc, char** argv)
{
	std::vector<Vector3d> vertices;
	vertices.push_back(Vector3d(0, 0, 0));
	vertices.push_back(Vector3d(0, 0, 1));
	vertices.push_back(Vector3d(0, 1, 0));
	vertices.push_back(Vector3d(0, 1, 1));
	vertices.push_back(Vector3d(1, 0, 0));
	vertices.push_back(Vector3d(1, 0, 1));
	vertices.push_back(Vector3d(1, 1, 0));
	vertices.push_back(Vector3d(1, 1, 1));
	std::vector<Triangle> triangles;
	triangles.push_back(Triangle({ 1,7,5 }));
	triangles.push_back(Triangle({ 1,3,7 }));
	triangles.push_back(Triangle({ 1,4,3 }));
	triangles.push_back(Triangle({ 1,2,4 }));
	triangles.push_back(Triangle({ 3,8,7 }));
	triangles.push_back(Triangle({ 3,4,8 }));
	triangles.push_back(Triangle({ 5,7,8 }));
	triangles.push_back(Triangle({ 5,8,6 }));
	triangles.push_back(Triangle({ 1,5,6 }));
	triangles.push_back(Triangle({ 1,6,2 }));
	triangles.push_back(Triangle({ 2,6,8 }));
	triangles.push_back(Triangle({ 2,8,4 }));
	

	/*=== CAMERA ===*/
	double focal(1);
	Vector3d cameraPosition(0, 0, 0);
	Vector3d cameraDirection(0, 0, 1);
	double nearPlaneDistance(0.5);
	double farPlaneDistance(100);
	double imageSize(2);
	std::pair<int, int> imageResolution(640, 480);
	Camera camera(cameraPosition, cameraDirection, focal, nearPlaneDistance, farPlaneDistance, imageSize, imageResolution);

	/*=== MATERIALS ===*/
	Material materialBlue(Color(64, 141, 147), 0.3, 0.3, 0.3, 100);
	Material materialRed(Color(255, 0, 0), 0.3, 0.3, 0.3, 50);
	Material materialGreen(Color(7, 163, 46), 0.3, 0.3, 0.3, 100);
	Material materialLightgrey(Color(166, 166, 166), 0.3, 0.3, 0.3, 10);

	/*=== LIGHT SOURCES ===*/
	LightSource light(Vector3d(0, 50, -50));

	/*=== OBJECTS ===*/
	Sphere sphere(materialBlue, Vector3d(0, -0.1, 5), 1);
	//Cube cube(materialRed,Vector3d(0,0,1),vertices, triangles);
	Plane planeHorizontal(materialLightgrey, Vector3d(0, -1, 0), Vector3d(0, 1, 0));
	Plane planeVertical(materialLightgrey, Vector3d(0, 0, 10), Vector3d(0, 0, -1));

	/*=== SCENE ===*/
	Scene scene(Vector3d(0,0,0), camera);
	scene.addLightSource(&light);
	scene.addObject(&sphere);
	scene.addObject(&planeHorizontal);
	scene.addObject(&planeVertical);
	scene.render();
	
	/*RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(256, 256, 32);

	color.rgbGreen = 0;
	for (size_t i = 0; i < 640; i++)
	{
		color.rgbRed = i;

		for (size_t j = 0; j < 480; j++)
		{
			color.rgbBlue = j;

			FreeImage_SetPixelColor(image, i, j, &color);
		}
	}

	FreeImage_Save(FIF_BMP, image, "out.bmp");*/



	return EXIT_SUCCESS;
}