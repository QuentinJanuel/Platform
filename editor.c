#include "editor.h"

void getBlocksCode(const Blocks blocks){
	int i = 0;
	for(; i < blocks.number; i++)
		fprintf(stdout, "newBlock(b, %d, %d, %d, %d);\n",
			blocks.b[i].x,
			blocks.b[i].y,
			blocks.b[i].width,
			blocks.b[i].height);
}

void mouseCreateBlock(Blocks *blocks, int x1, int y1, int x2, int y2){
	if(x1 > x2)
		swap(&x1, &x2);
	if(y1 > y2)
		swap(&y1, &y2);
	newBlock(blocks, x1, y1, x2-x1, y2-y1);
}

void mouseDeleteBlock(Blocks *blocks, const int mX, const int mY){
	int i = 0, j;
	Block b;
	for(; i < blocks->number; i++){
		b = blocks->b[i];
		if(collide(b.x, b.y, b.width, b.height, mX, mY, 1, 1)){
			for(j = i; j < blocks->number-1; j++)
				blocks->b[j] = blocks->b[j+1];
			blocks->number--;
		}
	}
}

void handleMouseEditor(Window *w, Mouse *m, Blocks *blocks, const int space){
	SDL_Event e = w->events;
	switch(e.type){
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.button == SDL_BUTTON_LEFT){
				m->x1 = e.button.x-e.button.x%space;
				m->y1 = e.button.y-e.button.y%space;
				m->pressed = true;
			}
			break;
		case SDL_MOUSEMOTION:
			m->x = e.button.x-e.button.x%space;
			m->y = e.button.y-e.button.y%space;
			break;
		case SDL_MOUSEBUTTONUP:
			switch(e.button.button){
				case SDL_BUTTON_LEFT:
					if(abs(m->x1-m->x) >= space && abs(m->y1-m->y) >= space)
						mouseCreateBlock(blocks, m->x1, m->y1, m->x, m->y);
					m->pressed = false;
					break;
				case SDL_BUTTON_RIGHT:
					mouseDeleteBlock(blocks, e.button.x, e.button.y);
			}
	}
}

void drawEditorRect(Window *w, const Mouse m){
	if(m.pressed){
		setAlpha(w, 0.5);
		drawRect(w, (m.x > m.x1) ? m.x1 : m.x, (m.y > m.y1) ? m.y1 : m.y, abs(m.x-m.x1), abs(m.y-m.y1));
		setAlpha(w, 1);
	}
}

void drawGrid(Window *w, const int space){
	int i;
	setColor(w, 0x222);
	for(i = 0; i < w->width; i += space)
		drawRect(w, i, 0, 1, w->height);
	for(i = 0; i < w->height; i += space)
		drawRect(w, 0, i, w->width, 1);
}
