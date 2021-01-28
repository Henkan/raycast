#include "Scene.h"
#include <iostream>
#include <FreeImage.h>

Scene::Scene(Vector3d origin, Camera camera) : origin(origin), camera(camera), objects(std::vector<Object3d*>()) {}

void Scene::addObject(Object3d* object)
{
	objects.push_back(object);
}

void Scene::render()
{

	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(camera.getResolution().first, camera.getResolution().second, 32);

	std::pair<int,int> resolution = camera.getResolution();
	double imageSize = camera.getImageSize();
	Vector3d position = camera.getPosition();
	Vector3d direction = camera.getDirection();
	double focal = camera.getFocal();

	double imageSizeHeight = (resolution.second * imageSize/ resolution.first);
	std::cout << imageSizeHeight << "\n";
	Vector3d topLeftCorner((position.getX() - imageSize / 2), position.getY() + imageSizeHeight / 2, position.getZ() + direction.getZ() * focal);
	for (int x = 0; x < resolution.first; ++x) {
		for (int y = 0; y < resolution.second; ++y) {

			Vector3d pixelPosition(topLeftCorner.getX() + x * imageSize / resolution.first, topLeftCorner.getY() - y * imageSizeHeight / resolution.second, topLeftCorner.getZ());
			Object3d* objectCollided = camera.sendRay(Ray(Vector3d(position), position.getDirection(pixelPosition)), objects);
			if ( objectCollided != nullptr) {
				std::map<char, int> colorObject = objectCollided->getColor();
				color.rgbRed = colorObject.at('r') ;
				color.rgbGreen = colorObject.at('g');
				color.rgbBlue = colorObject.at('b');
			}
			else {
				color.rgbRed = 0;
				color.rgbGreen = 0;
				color.rgbBlue = 0;
			}
			FreeImage_SetPixelColor(image, x, resolution.second - y, &color);
		}
	}
	FreeImage_Save(FIF_BMP, image, "out.bmp");
}
