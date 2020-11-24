#include "platform.h"

Platform* createPlatform(char* title, int windowW, int windowH, int chipDisplayW, int chipDisplayH)
{
	Platform* p = malloc(sizeof(Platform));

	if (!p)
	{
		printf("Error Allocating Memory for Platform");
		return NULL;
	}

	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL Initialization Error: %s", SDL_GetError());
		destroyPlatform(p);
		return NULL;
	}

	p->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, SDL_WINDOW_SHOWN);
	if (!p->window)
	{
		printf("Error Creating Window: %s", SDL_GetError());
		destroyPlatform(p);
		return NULL;
	}

	p->renderer = SDL_CreateRenderer(p->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!p->renderer)
	{
		printf("Error Creating Renderer: %s", SDL_GetError());
		destroyPlatform(p);
		return NULL;
	}

	p->chipDisplay = SDL_CreateTexture(p->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, chipDisplayW, chipDisplayH);
	
	return p;
}

void destroyPlatform(Platform* p)
{
	if (p->chipDisplay) { SDL_DestroyTexture(p->chipDisplay); }
	if (p->renderer) { SDL_DestroyRenderer(p->renderer); }
	if (p->window) { SDL_DestroyWindow(p->window); }

	SDL_Quit();
	free(p);
}

void updatePlatform(Platform* p, const void* video_buffer, int pitch)
{
	SDL_UpdateTexture(p->chipDisplay, NULL, video_buffer, pitch);
	SDL_RenderClear(p->renderer);

	SDL_RenderCopy(p->renderer, p->chipDisplay, NULL, NULL);
	SDL_RenderPresent(p->renderer);
}

bool mapInput(uint8_t* keys)
{
	bool quit = false;
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;

			case SDLK_x:
				keys[0] = 1;
				break;

			case SDLK_1:
				keys[1] = 1;
				break;

			case SDLK_2:
				keys[2] = 1;
				break;

			case SDLK_3:
				keys[3] = 1;
				break;

			case SDLK_q:
				keys[4] = 1;
				break;

			case SDLK_w:
				keys[5] = 1;
				break;

			case SDLK_e:
				keys[6] = 1;
				break;

			case SDLK_a:
				keys[7] = 1;
				break;

			case SDLK_s:
				keys[8] = 1;
				break;

			case SDLK_d:
				keys[9] = 1;
				break;

			case SDLK_z:
				keys[0xA] = 1;
				break;

			case SDLK_c:
				keys[0xB] = 1;
				break;

			case SDLK_4:
				keys[0xC] = 1;
				break;

			case SDLK_r:
				keys[0xD] = 1;
				break;

			case SDLK_f:
				keys[0xE] = 1;
				break;

			case SDLK_v:
				keys[0xF] = 1;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_x:
				keys[0] = 0;
				break;

			case SDLK_1:
				keys[1] = 0;
				break;

			case SDLK_2:
				keys[2] = 0;
				break;

			case SDLK_3:
				keys[3] = 0;
				break;

			case SDLK_q:
				keys[4] = 0;
				break;

			case SDLK_w:
				keys[5] = 0;
				break;

			case SDLK_e:
				keys[6] = 0;
				break;

			case SDLK_a:
				keys[7] = 0;
				break;

			case SDLK_s:
				keys[8] = 0;
				break;

			case SDLK_d:
				keys[9] = 0;
				break;

			case SDLK_z:
				keys[0xA] = 0;
				break;

			case SDLK_c:
				keys[0xB] = 0;
				break;

			case SDLK_4:
				keys[0xC] = 0;
				break;

			case SDLK_r:
				keys[0xD] = 0;
				break;

			case SDLK_f:
				keys[0xE] = 0;
				break;

			case SDLK_v:
				keys[0xF] = 0;
				break;
			}
			break;
		}
	}

	return quit;
}