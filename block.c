#include "block.h"

Block createBlock(const int x, const int y, const int width, const int height){
	Block b = {x, y};
	b.color = 0x000;
	b.width = width;
	b.height = height;
	return b;
}

void drawBlock(Window *w, const Block b){
	setColor(w, b.color);
	drawRect(w, b.x, b.y, b.width, b.height);
}

Blocks initBlocks(const int max){
	Block *block = malloc(max*sizeof(*block));
	Blocks blocks;
	blocks.number = 0;
	blocks.b = block;
	return blocks;
}

void drawAllBlocks(Window *w, const Blocks allBlocks){
	int i = 0;
	for(; i < allBlocks.number; i++){
		drawBlock(w, allBlocks.b[i]);
	}
}

void newBlock(Blocks *blocks, const int x, const int y, const int width, const int height){
	blocks->b[blocks->number++] = createBlock(x, y, width, height);
}

void freeBlocks(Blocks *blocks){
	free(blocks->b);
}
