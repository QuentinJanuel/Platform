#include "window.h"
#include <bool.h>
#include "keyboard.h"
#include "block.h"
#include "player.h"
#include "level.h"

int main(int argc, char *argv[]){
	Window *win = createWindow(800, 608, "Platform game", 50);
	Keyboard key = {false};

	Blocks blocks = initBlocks(1000);
	makeLevel(&blocks);

	Player p1 = newPlayer(150, 500);

	int imgMario = loadImage(win, "images/mario.png");
	
	bool close = false;
	SDL_Event e;
	while(!close){
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)){
				close = true;
			}
			key.preUp = key.up;
			getKey(&key.up, e, SDLK_UP);
			getKey(&key.left, e, SDLK_LEFT);
			getKey(&key.right, e, SDLK_RIGHT);
		}
		while(SDL_GetTicks()-win->pTime < 1000.0/win->FPS);
		screenClear(win);
		setColor(win, 0xAAA);
		drawRect(win, 0, 0, win->width, win->height);
		//
		updatePlayer(key, &p1, blocks);
		drawAllBlocks(win, blocks);
		drawPlayer(win, p1);
		drawImage(win, imgMario, 0, 0);
		//
		SDL_Flip(win->screen);
		win->pTime = SDL_GetTicks();
	}
	endSDL(win);
	return EXIT_SUCCESS;
}