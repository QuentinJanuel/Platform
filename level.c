#include "level.h"

void makeLevel(Blocks *b){
	newBlock(b, 32, 544, 736, 32);
	newBlock(b, 64, 480, 32, 64);
	newBlock(b, 96, 448, 32, 96);
	newBlock(b, 256, 480, 32, 64);
	newBlock(b, 288, 448, 32, 96);
	newBlock(b, 320, 512, 32, 32);
	newBlock(b, 416, 480, 96, 32);
	newBlock(b, 576, 96, 32, 480);
}
