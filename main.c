#include "window.h"
#include <bool.h>
#include "keyboard.h"
#include "block.h"
#include "player.h"
#include "level.h"

int main(int argc, char *argv[]){
	Window *win = createWindow(800, 608, "Platform game", 70);
	Keyboard key = {false};
	int imgBackground = loadImage(win, "images/background.png");

	Player p1 = newPlayer(win, 150, 500);
	Blocks blocks = initBlocks(1000);
	makeLevel(&blocks);

	int x1 = 0, y1 = 0, i, j;
	
	bool close = false;
	SDL_Event e;
	while(!close){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				close = true;
			else if(e.type == SDL_MOUSEBUTTONDOWN){
				if(e.button.button == SDL_BUTTON_LEFT){
					x1 = e.button.x;
					y1 = e.button.y;
				}
			}else if(e.type == SDL_MOUSEBUTTONUP){
				switch(e.button.button){
					case SDL_BUTTON_LEFT:
						newBlock(&blocks,	(e.button.x > x1) ? x1 : e.button.x,
											(e.button.y > y1) ? y1 : e.button.y,
											(e.button.x > x1) ? e.button.x-x1 : x1-e.button.x,
											(e.button.y > y1) ? e.button.y-y1 : y1-e.button.y);
						break;
					case SDL_BUTTON_RIGHT:
						for(i = 0; i < blocks.number; i++){
							if(e.button.x > blocks.b[i].x && e.button.y > blocks.b[i].y &&
							e.button.x < blocks.b[i].x+blocks.b[i].width && e.button.y < blocks.b[i].y+blocks.b[i].height){
								for(j = i; j < blocks.number-1; j++)
									blocks.b[j] = blocks.b[j+1];
								blocks.number--;
							}
						}
						break;
				}
			}
			key.preUp = key.up;
			getKey(&key.up, e, SDLK_UP);
			getKey(&key.left, e, SDLK_LEFT);
			getKey(&key.right, e, SDLK_RIGHT);
		}
		while(SDL_GetTicks()-win->pTime < 1000.0/win->FPS);
		screenClear(win);
		drawImage(win, imgBackground, 0, 0);
		//
		updatePlayer(key, &p1, blocks);
		drawAllBlocks(win, blocks);
		drawPlayer(win, p1);
		//
		SDL_Flip(win->screen);
		win->pTime = SDL_GetTicks();
	}
	for(i = 0; i < blocks.number; i++){
		fprintf(stdout, "newBlock(b, %d, %d, %d, %d);\n",
			blocks.b[i].x,
			blocks.b[i].y,
			blocks.b[i].width,
			blocks.b[i].height);
	}
	free(blocks.b);
	endSDL(win);
	return EXIT_SUCCESS;
}