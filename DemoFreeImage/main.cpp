#include <iostream>
#include "FreeImage.h"
#include "Engine/Scene.h"
#include "Objects/Cube.h"
#include "Objects/Sphere.h"
#include "Objects/Plane.h"
#include "Engine/Parser.h"
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
	bool useParser(true);
	Scene scene;
	if (argc == 2) {
		// Using parser
		useParser = true;
	}
	
	if (useParser) {
		//std::cout << "Reading scene from " << argv[1] << "...\n";
		//scene = Parser::parseFileIntoScene(argv[1]);
		scene = Parser::parseFileIntoScene("scene.txt");
	}
	else {
		std::cout << "Generating default scene...\n";

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
		LightSource light(Vector3d(0, 10, -30), Color(255, 255, 255));

		/*=== OBJECTS ===*/
		Plane planeVertical(materialLightgrey, Vector3d(0, 0, 10), Vector3d(0, 0, -1));

		Sphere sphere1(materialBlue, Vector3d(0, -1, 3), 1);
		Sphere sphere2(materialRed, Vector3d(2, 0, 4), 1);
		Sphere sphere3(materialGreen, Vector3d(-2, 0, 4), 1);
		Plane plane(materialGreen, Vector3d(0, -1, 0), Vector3d(0, 1, 0));

		/*=== SCENE ===*/
		scene = Scene(camera);
		scene.addLightSource(&light);
		scene.addObject(&sphere1);
		scene.addObject(&sphere2);
		scene.addObject(&sphere3);
		scene.addObject(&plane);
	}
	std::cout << "Rendering...\n";
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
			if (event.type == sf::Event::Closed) window.close();

		}
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return EXIT_SUCCESS;
}