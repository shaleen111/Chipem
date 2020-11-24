#ifndef CHIP8_H
#define CHIP8_H

#define FONTSET_SIZE 80
#define VWIDTH 64
#define VHEIGHT 32

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct chip8
{
	uint8_t registers[16];
	uint8_t memory[4096];
	uint16_t indexRegister;
	uint16_t pc;
	uint16_t stack[16];
	uint8_t sp;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t keys[16];
	uint32_t display[VWIDTH * VHEIGHT];
	uint16_t opCode; 

	bool drawFlag;

	void (*opCodes[0x10]) (struct chip8* t);
	void (*table0[0xF]) (struct chip8* t);
	void (*table8[0xF]) (struct chip8* t);
	void (*tableE[0xF]) (struct chip8* t);
	void (*tableF[0x66]) (struct chip8* t);
} chip8;

chip8* createChip8();
void destroyChip8(chip8* t);
int loadROM(chip8* t, const char* filename);
void Table0(chip8 *t);
void Table8(chip8 *t);
void TableE(chip8 *t);
void TableF(chip8 *t);
void cycleCPU(chip8* t);
void updateTimers(chip8* t);


int getRandomNumber(int lower, int upper);


// INSTRUCTION SET
void O00E0(chip8* t);
void O00EE(chip8* t);
void O1nnn(chip8* t);
void O2nnn(chip8* t);
void O3xkk(chip8* t);
void O4xkk(chip8* t);
void O5xy0(chip8* t);
void O6xkk(chip8* t);
void O7xkk(chip8* t);
void O8xy0(chip8* t);
void O8xy1(chip8* t);
void O8xy2(chip8* t);
void O8xy3(chip8* t);
void O8xy4(chip8* t);
void O8xy5(chip8* t);
void O8xy6(chip8* t);
void O8xy7(chip8* t);
void O8xyE(chip8* t);
void O9xy0(chip8* t);
void OAnnn(chip8* t);
void OBnnn(chip8* t);
void OCxkk(chip8* t);
void ODxyn(chip8* t);
void OEx9E(chip8* t);
void OExA1(chip8* t);
void OFx07(chip8* t);
void OFx0A(chip8* t);
void OFx15(chip8* t);
void OFx18(chip8* t);
void OFx1E(chip8* t);
void OFx29(chip8* t);
void OFx33(chip8* t);
void OFx55(chip8* t);
void OFx65(chip8* t);

#endif