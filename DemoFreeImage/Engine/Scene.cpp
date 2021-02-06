#include "Scene.h"
#include <iostream>
#include <FreeImage.h>

Scene::Scene()
{
}

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

	std::pair<int,int> resolution = camera.getResolution();
	double imageSize = camera.getImageSize();
	Vector3d position = camera.getPosition();
	Vector3d direction = camera.getDirection();
	double focal = camera.getFocal();

	double imageSizeHeight = (resolution.second * imageSize/ resolution.first);

	Vector3d topLeftCorner((position.getX() - imageSize / 2), position.getY() + imageSizeHeight / 2, position.getZ() + direction.getZ() * focal);
	for (int x = 0; x < resolution.first; ++x) {
		for (int y = 0; y < resolution.second; ++y) {

			Vector3d pixelPosition(topLeftCorner.getX() + x * imageSize / resolution.first, topLeftCorner.getY() - y * imageSizeHeight / resolution.second, topLeftCorner.getZ());
			std::pair<Object3d*, Vector3d> objectAndPosCollided = camera.sendRay(Ray(Vector3d(position), position.getDirection(pixelPosition)), objects);
			Object3d* objectCollided = objectAndPosCollided.first;
			Vector3d collisionPoint = objectAndPosCollided.second;

			if (objectCollided != nullptr) {

				Material matObject = objectCollided->getMaterial();
				
				Vector3d dirCameraNorm = collisionPoint.getDirection(camera.getPosition());
				dirCameraNorm.normalize();

				Vector3d surfaceNormaleNorm = objectCollided->getNormalVectorOfSurface(collisionPoint);
				surfaceNormaleNorm.normalize();
				
				Color ambient((int)(matObject.getColor().getRed() * matObject.getAmbient()),
					(int)(matObject.getColor().getGreen() * matObject.getAmbient()),
					(int)(matObject.getColor().getBlue() * matObject.getAmbient()));
				
				Color pixelColor = ambient;

				for (auto light : lightSources) {

					Vector3d dirTowardsLightNorm = collisionPoint.getDirection(light->getPosition());
					dirTowardsLightNorm.normalize();
					
					Ray rayToLight(collisionPoint, dirTowardsLightNorm); //Secondary ray
					std::vector<Object3d*> otherObjets = objects;
					//Find the object where the collision happened and remove it to avoid autocollision
					auto it = std::find(otherObjets.begin(), otherObjets.end(), objectCollided); 
					if (it != otherObjets.end()) {
						otherObjets.erase(it);
					}
					// If there is an object blocking light, skip light effect
					if (camera.sendRay(rayToLight, otherObjets).first != nullptr) {
						continue;
					}
					Vector3d lightReflectionNorm = dirTowardsLightNorm.getReflected(surfaceNormaleNorm);
					lightReflectionNorm.normalize();

					Vector3d medianDirCamLight = (dirTowardsLightNorm + dirCameraNorm) / (dirTowardsLightNorm + dirCameraNorm).getNorm();
					
					double attenuationFunction = (1 / (light->getPosition().getDirection(collisionPoint).getLength()));
					
					Color diffuse((int)(matObject.getColor().getRed() * matObject.getDiffuse() * attenuationFunction * light->getColor().getRed() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm)),
						(int)(matObject.getColor().getGreen() * matObject.getDiffuse() * attenuationFunction * light->getColor().getGreen() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm)),
						(int)(matObject.getColor().getBlue() * matObject.getDiffuse() * attenuationFunction * light->getColor().getBlue() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm)));
					//diffuse.correctRange();


					Color specular((int)(75*matObject.getSpecular() * attenuationFunction * light->getColor().getRed() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), matObject.getShininess())),
						(int)(75*matObject.getSpecular() * attenuationFunction * light->getColor().getGreen() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), matObject.getShininess())),
						(int)(75*matObject.getSpecular() * attenuationFunction * light->getColor().getBlue() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), matObject.getShininess())));
					//specular.correctRange();

					pixelColor = pixelColor + specular + diffuse;
				}

				/*if (!lightSources.empty()) {
					double coeff = 0.7;
					Color ambientLightColor(matObject.getColor().getRed() * coeff, matObject.getColor().getGreen() * coeff, matObject.getColor().getBlue() * coeff);
					pixelColor = pixelColor + ambientLightColor;
				}*/

				pixelColor.correctRange();
				color.rgbRed = pixelColor.getRed();
				color.rgbGreen = pixelColor.getGreen();
				color.rgbBlue = pixelColor.getBlue();
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

void Scene::printObjects()
{
	std::cout << objects[0]->getMaterial().getColor().getBlue()<< std::endl;
}

void Scene::printLight()
{
	lightSources[0]->getColor().print();
}


Scene::~Scene()
{
}
