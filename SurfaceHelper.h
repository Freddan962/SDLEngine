#ifndef SURFACEHELPER_H
#define SURFACEHELPER_H

#include "SDL.h"

class SurfaceHelper
{
public:
	static bool isTransparent(SDL_Surface* surface, int x, int y)
	{
		int bytesPerPixel = surface->format->BytesPerPixel;	
		//Grab pointer to pixel with x and y offset and bytesPerPixel modifier (how many bytes the pixel is built up by in memory)
		Uint8* pixel = (Uint8*)surface->pixels + y * surface->pitch + x * bytesPerPixel; 
		Uint32 pixelColor; //SDL_Surface->pixels store pixel data with 8 bits for r

		switch (bytesPerPixel)
		{
		case(1):
			pixelColor = *pixel;
			break;
		case(2):
			pixelColor = *(Uint16*)pixel;
			break;
		case(3):
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelColor = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
			else
				pixelColor = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
			break;
		case(4):
			pixelColor = *(Uint32*)pixel;
			break;
		}

		Uint8 r, g, b, alpha;
		SDL_GetRGBA(pixelColor, surface->format, &r, &g, &b, &alpha); //Can't call with null arguments, causes crash

		return alpha < alphaThreshold;
	}

private:
	static const int alphaThreshold = 50; //255 = no alpha at all
};

#endif