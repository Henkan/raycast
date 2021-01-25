#include <iostream>
#include "FreeImage.h"

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
	
	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(256, 256, 32);

	int a;
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

	FreeImage_Save(FIF_BMP, image, "out.bmp");

	return EXIT_SUCCESS;
}