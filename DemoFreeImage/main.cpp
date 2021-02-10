#include <iostream>
#include "FreeImage.h"
#include "Engine/Scene.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Engine/Parser.h"

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
	/*std::vector<Vector3d> vertices;
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
	triangles.push_back(Triangle({ 2,8,4 }));*/

	Scene sceneTest = Parser::parseFileIntoScene("scene.txt");
	sceneTest.render();

	
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
	Material materialBlue(Color(64, 141, 147), 0.1, 0.3, 0.3, 100);
	Material materialRed(Color(255, 0, 0), 0.3, 0.3, 0.3, 100);
	Material materialGreen(Color(7, 163, 46), 0.3, 0.3, 0.3, 100);
	Material materialLightgrey(Color(166, 166, 166), 0.3, 0.3, 0.3, 10);

	/*=== LIGHT SOURCES ===*/
	//LightSource light(Vector3d(0, 10, 50));
	LightSource light(Vector3d(0, 10, -30), Color(255, 255, 255));

	/*=== OBJECTS ===*/
	Plane planeVertical(materialLightgrey, Vector3d(0, 0, 10), Vector3d(0, 0, -1));

	Sphere sphere1(materialBlue, Vector3d(0, -1, 3), 1);
	Sphere sphere2(materialRed, Vector3d(2, 0, 4), 1);
	Sphere sphere3(materialGreen, Vector3d(-2, 0, 4), 1);
	Plane plane(materialGreen, Vector3d(0, -1, 0), Vector3d(0, 1, 0));
	//Sphere sphere4(Material(Color(255, 255, 0), 0.3, 0.3, 0.3, 100), Vector3d(0, -5001, 0), 5000);
	std::array<Vector3d, 3> vertices;
	vertices[0] = Vector3d(0, -1, 7);
	vertices[1] = Vector3d(-1, -0.99999, 2);
	vertices[2] = Vector3d(1, -1, 2);
	Triangle triangle(materialRed, vertices);
	Sphere sphere4(materialRed, Vector3d(0, -1, 7), 0.5);
	Sphere sphere5(materialRed, Vector3d(-1, -1, 2), 0.5);
	Sphere sphere6(materialRed, Vector3d(1, -1, 2), 0.5);
	/*=== SCENE ===*/
	Scene scene(camera);
	scene.addLightSource(&light);
	//scene.addObject(&sphere);
	//scene.addObject(&sphere1);
	//scene.addObject(&sphere2);
	//scene.addObject(&sphere3);
	//scene.addObject(&plane);
	//scene.addObject(&planeHorizontal);
	//scene.addObject(&planeVertical);
	scene.addObject(&triangle);
	//scene.addObject(&sphere4);
	//scene.addObject(&sphere5);
	//scene.addObject(&sphere6);
	//scene.render();

	
	return EXIT_SUCCESS;
}