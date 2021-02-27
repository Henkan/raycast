#include "Scene.h"
#include <iostream>
#include <FreeImage.h>

Scene::Scene(Camera camera) : camera(camera), objects(std::vector<Object3d*>()), lightSources(std::vector<LightSource*>()) {}

void Scene::addCamera(Camera camera)
{
	this->camera = camera;
}

Camera Scene::getCamera()
{
	return camera;
}

void Scene::addObject(Object3d* object)
{
	objects.push_back(object);
}

void Scene::addObjects(std::vector<Object3d*> listObjects)
{
	objects.insert(objects.end(), listObjects.begin(), listObjects.end());
}

void Scene::addLightSource(LightSource* lightSource)
{
	lightSources.push_back(lightSource);
}

void Scene::addLightSources(std::vector<LightSource*> lightSourcesToAdd)
{
	lightSources.insert(lightSources.end(), lightSourcesToAdd.begin(), lightSourcesToAdd.end());
}

void Scene::render()
{
	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(camera.getResolution().first, camera.getResolution().second, 32);

	std::pair<int, int> resolution = camera.getResolution();
	double imageSize(camera.getImageSize());
	Vector3d position(camera.getPosition());
	Vector3d direction(camera.getDirection());
	double focal(camera.getFocal());

	double imageSizeHeight = (resolution.second * imageSize / resolution.first);
	Vector3d topLeftCorner((position.getX() - imageSize / 2), position.getY() + imageSizeHeight / 2, position.getZ() + direction.getZ() * focal);

	for (int x = 0; x < resolution.first; ++x) {
		for (int y = 0; y < resolution.second; ++y) {

			// Position of the current pixel in the scene coordinates
			Vector3d initialPixelPosition(topLeftCorner.getX() + x * imageSize / resolution.first, topLeftCorner.getY() - y * imageSizeHeight / resolution.second, topLeftCorner.getZ());

			// Anti-aliasing works by sub-dividing each pixel
			std::vector<Color> colors;
			for (int x2 = 0; x2 < 2; ++x2) {
				double stepX = (topLeftCorner.getX() + (x + 1) * imageSize / resolution.first) - (topLeftCorner.getX() + x * imageSize / resolution.first);
				stepX /= 2;
				for (int y2 = 0; y2 < 2; ++y2) {
					double stepY = (topLeftCorner.getY() - (y + 1) * imageSizeHeight / resolution.second) - (topLeftCorner.getY() - y * imageSizeHeight / resolution.second);
					stepY /= 2;

					Vector3d pixelPosition(initialPixelPosition.getX() + x2 * stepX, initialPixelPosition.getY() - y2 * stepY, initialPixelPosition.getZ());

					std::pair<Object3d*, Vector3d> objectAndPosCollided(camera.sendRay(Ray(Vector3d(position), position.getDirection(pixelPosition)), objects));
					Object3d* objectCollided(objectAndPosCollided.first);
					Vector3d collisionPoint(objectAndPosCollided.second);

					if (objectCollided != nullptr) {
						// Ray hits an object
						Material matObject(objectCollided->getMaterial());

						Vector3d dirCameraNorm(collisionPoint.getDirection(camera.getPosition()));
						dirCameraNorm.normalize();

						Vector3d surfaceNormaleNorm(objectCollided->getNormalVectorOfSurface(collisionPoint));
						surfaceNormaleNorm.normalize();

						Color ambient(matObject.computeAmbient());
						Color pixelColor;

						// Apply default color if there is no light
						if (lightSources.empty()) pixelColor = ambient;

						for (auto light : lightSources) {

							Vector3d dirTowardsLightNorm(collisionPoint.getDirection(light->getPosition()));
							dirTowardsLightNorm.normalize();

							// Move slightly the origin of the ray to avoid having a collision with itself
							Vector3d rayToLightStartPoint(collisionPoint + dirTowardsLightNorm * 0.01);
							Ray rayToLight(rayToLightStartPoint, dirTowardsLightNorm); //Secondary ray

							// If there is an object blocking light, skip light effect
							std::pair<Object3d*, Vector3d> result = camera.sendRay(rayToLight, objects);
							Object3d* blockingObject = result.first;
							Vector3d intersectionRayBlockingObject = result.second;
							if (blockingObject != nullptr) {
								// If objects are too close, skip light effect
								if (abs((rayToLight.getPosition() - intersectionRayBlockingObject).getLength()) > 0.1) {
									pixelColor = pixelColor + ambient;
									continue;
								}
							}

							Vector3d lightReflectionNorm = dirTowardsLightNorm.getReflected(surfaceNormaleNorm);
							lightReflectionNorm.normalize();

							Vector3d medianDirCamLight((dirTowardsLightNorm + dirCameraNorm) / (dirTowardsLightNorm + dirCameraNorm).getNorm());
							double attenuationFunction(1 / (light->getPosition().getDirection(collisionPoint).getLength()));

							// Compute light effect on color
							Color diffuse(matObject.computeDiffuse(*light, attenuationFunction, surfaceNormaleNorm.dotProduct(dirTowardsLightNorm)));
							diffuse.correctRange();
							Color specular(matObject.computeSpecular(*light, attenuationFunction, surfaceNormaleNorm.dotProduct(medianDirCamLight)));
							specular.correctRange();

							// Reflection
							Vector3d reflectedRayDir = position.getDirection(collisionPoint) + (surfaceNormaleNorm * 2 * (-position.getDirection(collisionPoint).dotProduct(surfaceNormaleNorm)));

							// Move slightly the origin of the ray to avoid collision
							Ray reflectedRay(collisionPoint + reflectedRayDir * 0.001, reflectedRayDir);

							Object3d* reflectedObject = camera.sendRay(reflectedRay, objects).first;
							Color reflectedAmbient;
							if (reflectedObject != nullptr) {
								reflectedAmbient = Color(reflectedObject->getMaterial().computeAmbient());
							}
							else {
								reflectedAmbient = Color(0, 0, 0);
							}

							double red = ambient.getRed() * (1.0 - matObject.getReflectivity()) + (reflectedAmbient.getRed() * matObject.getReflectivity());
							double green = ambient.getGreen() * (1.0 - matObject.getReflectivity()) + reflectedAmbient.getGreen() * matObject.getReflectivity();
							double blue = ambient.getBlue() * (1.0 - matObject.getReflectivity()) + reflectedAmbient.getBlue() * matObject.getReflectivity();
							pixelColor = pixelColor + Color(red, green, blue) + specular + (diffuse * (1.0 - matObject.getReflectivity()));
						}
						pixelColor.correctRange();
						colors.push_back(pixelColor);
					}
					else {
						// No object => draw black
						colors.push_back(Color(0, 0, 0));
					}
				}
			}

			// Compute final color by applying the mean value
			double red = 0;
			double green = 0;
			double blue = 0;
			for (auto color : colors) {
				red += color.getRed();
				green += color.getGreen();
				blue += color.getBlue();
			}
			red /= colors.size();
			green /= colors.size();
			blue /= colors.size();

			// Apply the color to the image
			color.rgbRed = red;
			color.rgbGreen = green;
			color.rgbBlue = blue;
			FreeImage_SetPixelColor(image, x, resolution.second - y, &color);
		}
	}
	FreeImage_Save(FIF_BMP, image, "out.bmp");
}

void Scene::printObjects()
{
	std::cout << objects[0]->getMaterial().getColor().getBlue() << std::endl;
}

void Scene::printLight()
{
	lightSources[0]->getColor().print();
}


Scene::~Scene()
{
	for (auto object : objects) {
		delete object;
	}
	objects.clear();
	for (auto light : lightSources) {
		delete light;
	}
	lightSources.clear();
}
