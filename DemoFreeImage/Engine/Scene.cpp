#include "Scene.h"
#include <iostream>
#include <FreeImage.h>

Scene::Scene(Vector3d origin, Camera camera) : origin(origin), camera(camera), objects(std::vector<Object3d*>()), lightSources(std::vector<LightSource*>()) {}

void Scene::addObject(Object3d* object)
{
	objects.push_back(object);
}

void Scene::addLightSource(LightSource* lightSource)
{
	lightSources.push_back(lightSource);
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

			if ( objectCollided != nullptr) {
				//collisionPoint = Vector3d(0, 1, 5); //aaa
				Material matObject = objectCollided->getMaterial();
				
				Vector3d dirCameraNorm = collisionPoint.getDirection(camera.getPosition());
				dirCameraNorm.normalize();

				Vector3d surfaceNormaleNorm = objectCollided->getNormalVectorOfSurface(collisionPoint);
				surfaceNormaleNorm.normalize();

				//TODO : For each light
				LightSource light = *lightSources[0];

				Vector3d dirTowardsLightNorm = collisionPoint.getDirection(light.getPosition());
				dirTowardsLightNorm.normalize();

				Vector3d lightReflectionNorm = dirTowardsLightNorm.getReflected(surfaceNormaleNorm);
				lightReflectionNorm.normalize();

				Vector3d medianDirCamLight = (dirTowardsLightNorm + dirCameraNorm) / (dirTowardsLightNorm + dirCameraNorm).getNorm();
				// JUSQUE LA CEST GOOD

				double attenuationFunction = (1 / light.getPosition().getDirection(collisionPoint).getLength());
				Color ambient(matObject.getColor().getRed() * matObject.getAmbient(),
					matObject.getColor().getGreen() * matObject.getAmbient(),
					matObject.getColor().getBlue() * matObject.getAmbient());

				Color diffuse(matObject.getColor().getRed() * matObject.getDiffuse() * attenuationFunction * light.getColor().getRed() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm),
					matObject.getColor().getGreen() * matObject.getDiffuse() * attenuationFunction * light.getColor().getGreen() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm),
					matObject.getColor().getBlue() * matObject.getDiffuse() * attenuationFunction * light.getColor().getBlue() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm));

				Color specular(matObject.getSpecular() * attenuationFunction * light.getColor().getRed() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), lightSources.size()),
					matObject.getSpecular() * attenuationFunction * light.getColor().getGreen() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), lightSources.size()),
					matObject.getSpecular() * attenuationFunction * light.getColor().getBlue() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), lightSources.size()));
				
				Color pixelColor = ambient + specular + diffuse;
				//pixelColor = diffuse;
				//specular.print();
				//pixelColor = specular;
				//AMBIENT OK ? POTETRE
				//std::cout << surfaceNormaleNorm.dotProduct(medianDirCamLight) << "\n";


				//pixelColor = specular;
				/*pixelColor = diffuse;
				std::cout << "Object: ";
				matObject.getColor().print();
				std::cout << "Light: ";
				light.getColor().print();*/

				//double ambientIntensity = light.getIntensity() * matObject.getAmbient();
				//double diffuseIntensity = (1 / light.getPosition().getDirection(collisionPoint).getLength()) * light.getIntensity() * surfaceNormaleNorm.dotProduct(dirTowardsLightNorm);
				//double specularIntensity = (1 / light.getPosition().getDirection(collisionPoint).getLength()) * light.getIntensity() * pow(surfaceNormaleNorm.dotProduct(medianDirCamLight), lightSources.size());

				//double totalIntensity = ambientIntensity * matObject.getAmbient() + diffuseIntensity * matObject.getDiffuse() + specularIntensity * matObject.getSpecular();
				//std::cout << totalIntensity << "\n";
				//   finalColor = ambient+lambertianTerm * surfaceColor * lightColor + specularIntensity * specularColor * lightColor;
				if (pixelColor.getRed() > 255) color.rgbRed = 255;
				else if (pixelColor.getRed() < 0) color.rgbRed = 0;
				else color.rgbRed = pixelColor.getRed();
				if (pixelColor.getGreen() > 255) color.rgbGreen = 255;
				else if (pixelColor.getGreen() < 0) color.rgbGreen = 0;
				else color.rgbGreen = pixelColor.getGreen();
				if (pixelColor.getBlue() > 255) color.rgbBlue = 255;
				else if (pixelColor.getBlue() < 0) color.rgbBlue = 0;
				else color.rgbBlue = pixelColor.getBlue();
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
