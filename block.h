#ifndef BLOCK
#define BLOCK

#include "window.h"

typedef struct Block{
	int x;
	int y;
	int color;
	int width;
	int height;
} Block;

typedef struct Blocks{
	Block *b;
	int number;
} Blocks;

Block createBlock(const int, const int, const int, const int);

void drawBlock(Window*, const Block);

Blocks initBlocks(const int);

void drawAllBlocks(Window*, const Blocks);

void newBlock(Blocks*, const int, const int, const int, const int);

#endif //BLOCK