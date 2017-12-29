#ifndef EDITOR
#define EDITOR

#include <math.h>
#include "standart.h"
#include "collision.h"
#include "block.h"

typedef struct Mouse{
	bool pressed;
	int x1;
	int y1;
	int x;
	int y;
} Mouse;

void getBlocksCode(const Blocks);

void mouseCreateBlock(Blocks*, int, int, int, int);

void mouseDeleteBlock(Blocks*, const int, const int);

void handleMouseEditor(Window*, Mouse*, Blocks*, const int);

void drawEditorRect(Window*, const Mouse);

void drawGrid(Window*, const int);

#endif //EDITOR