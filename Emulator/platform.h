#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* chipDisplay;
} Platform;

Platform* createPlatform(char* title, int windowW, int windowH, int chipDisplayW, int chipDisplayH);
void destroyPlatform(Platform* p);
void updatePlatform(Platform* p, void const *video_buffer, int pitch);
bool mapInput(uint8_t* keys);

#endif