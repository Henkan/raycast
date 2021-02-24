#include <iostream>
#include "FreeImage.h"
#include "Engine/Scene.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Engine/Parser.h"
#include <SFML/Graphics.hpp>
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

	bool useParser(true);
	Scene scene;
	if (useParser) {
		scene = Parser::parseFileIntoScene("scene.txt");
	}
	else {
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
		Material materialBlue(Color(64, 141, 147), 0.1, 0.3, 0.3, 100, 0.0);
		Material materialRed(Color(255, 0, 0), 0.3, 0.3, 0.3, 50, 0);
		Material materialGreen(Color(7, 163, 46), 0.3, 0.3, 0.3, 100, 0);
		Material materialLightgrey(Color(166, 166, 166), 0.3, 0.3, 0.3, 10, 0);

		/*=== LIGHT SOURCES ===*/
		//LightSource light(Vector3d(0, 10, 50));
		LightSource light(Vector3d(0, 10, -30), Color(255, 255, 255));

		/*=== OBJECTS ===*/
		/*Sphere sphere(materialBlue, Vector3d(0, 0, 5), 1);
		Sphere sphere2(materialGreen, Vector3d(0, 1.5, 4), 1);
		//Cube cube(materialRed,Vector3d(0,0,1),vertices, triangles);
		Plane planeHorizontal(materialLightgrey, Vector3d(0, -1, 0), Vector3d(0, 1, 0));
		Plane planeVertical(materialLightgrey, Vector3d(0, 0, 10), Vector3d(0, 0, -1));*/
		Plane planeVertical(materialLightgrey, Vector3d(0, 0, 10), Vector3d(0, 0, -1));

		Sphere sphere1(materialBlue, Vector3d(0, -1, 3), 1);
		Sphere sphere2(materialRed, Vector3d(2, 0, 4), 1);
		Sphere sphere3(materialGreen, Vector3d(-2, 0, 4), 1);
		Plane plane(materialGreen, Vector3d(0, -1, 0), Vector3d(0, 1, 0));
		//Sphere sphere4(Material(Color(255, 255, 0), 0.3, 0.3, 0.3, 100), Vector3d(0, -5001, 0), 5000);

		/*=== SCENE ===*/
		Scene scene(camera);
		scene.addLightSource(&light);
		//scene.addObject(&sphere);
		scene.addObject(&sphere1);
		scene.addObject(&sphere2);
		scene.addObject(&sphere3);
		scene.addObject(&plane);
		//scene.addObject(&planeHorizontal);
		//scene.addObject(&planeVertical);
	}
	scene.render();
	
	sf::RenderWindow window(sf::VideoMode(scene.getCamera().getResolution().first, scene.getCamera().getResolution().second), "Raycasting woaw");
	sf::Texture texture;
	if (!texture.loadFromFile("out.bmp"))
	{
		std::cout << "No.";
		return 1;
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return EXIT_SUCCESS;
}