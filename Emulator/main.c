#include "main.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//if (argc != 3)
	//{
	//	printf("Usage: %s <scale> <path/to/file>", argv[0]);
	//	return 1;
	//}

	int scale = 10; /*atoi(argv[1])*/
	const char* filePath = "C:/Users/shale/source/repos/Emulator/Debug/roms/PONG"; /*argv[2]*/
	char windowTitle[100];

	sprintf(windowTitle, "Chip 8 - %s", filePath);

	Platform* platform = createPlatform(windowTitle, VWIDTH * scale, VHEIGHT * scale, VWIDTH, VHEIGHT);

	if (!platform)
	{
		return 1;
	}

	chip8* machine = createChip8();

	if (!machine)
	{
		return 1;
	}

	if (loadROM(machine, filePath))
	{
		return 1;
	}


	int pitch = sizeof(machine->display[0]) * VWIDTH;

	// number of opcodes to execute a second
	int timerClock = 60;
	int nOpCodes = 740;

	// number of opcodes to execute a frame 
	int nOpFrame = nOpCodes / timerClock;

	float interval = 1000;
	interval /= timerClock;

	unsigned int lastCycleT = SDL_GetTicks();

	bool q = false;
	while (!q)
	{
		/* 
			sleeping would likely be much better
			but on windows so its complicated
			(but not impossible) in C
		*/
		q = mapInput(machine->keys);
		unsigned int currentCycleT = SDL_GetTicks();
		int dt = currentCycleT - lastCycleT;
		if (dt >= interval)
		{
			updateTimers(machine);

			if (machine->soundTimer == 1)
			{
				// play beeeep
			}

			for (int i = 0; i < nOpFrame; i++)
			{
				cycleCPU(machine);
			}

			lastCycleT = currentCycleT;
			if (machine->drawFlag)
			{
				updatePlatform(platform, machine->display, pitch);
				machine->drawFlag = false;
				// printf("%f", 1 / (float) dt);
			}
		}
	}

	destroyChip8(machine);
	destroyPlatform(platform);
	return 0;
}