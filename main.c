#include <bool.h>
#include <math.h>
#include "window.h"
#include "keyboard.h"
#include "block.h"
#include "player.h"
#include "level.h"
#include "editor.h"

int main(int argc, char *argv[]){
	Window *win = createWindow(800, 608, "Super Mario", 70);
	Keyboard key = {false};
	Mouse editor = {false};

	int imgBackground = loadImage(win, "images/background.png");
	Player p1 = newPlayer(win, 150, 500);
	Blocks blocks = initBlocks(1000);
	makeLevel(&blocks);

	while(!win->closed){
		while(SDL_PollEvent(&win->events)){
			checkForClose(win);
			handleKeyboard(win, &key);
			handleMouseEditor(win, &editor, &blocks, 16);
		}
		updatePlayer(key, &p1, blocks);
		screenClear(win);
		drawImage(win, imgBackground, 0, 0);
		drawGrid(win, 32);
		drawAllBlocks(win, blocks);
		drawPlayer(win, p1);
		drawEditorRect(win, editor);
		SDL_Flip(win->screen);
		SDL_Delay((float) 1000/win->FPS);
	}
	getBlocksCode(blocks);
	freeBlocks(&blocks);
	closeWindow(win);
	return EXIT_SUCCESS;
}