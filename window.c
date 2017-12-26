#include "window.h"

void startSDL(void){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		SDL_ERROR()
	}
}

void endSDL(Window *w){
	free(w);
	SDL_Quit();
}

Window *createWindow(const int width, const int height, const char *title, const int FPS){
	startSDL();
	Window *w = malloc(sizeof(*w));
	w->width = width;
	w->height = height;
	w->FPS = FPS;
	w->pTime = 0;
	w->screen = SDL_SetVideoMode(w->width, w->height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(w->screen == NULL){
		SDL_ERROR()
	}
	screenClear(w);
	SDL_WM_SetCaption(title, NULL);
	//icon
	SDL_EnableKeyRepeat(10, 10);
	return w;
}

void screenClear(Window *w){
	setAlpha(w, 1);
	setColor(w, 0xFFF);
	SDL_FillRect(w->screen, NULL, w->color);
}

RGB hexToRGB(int hex){
	int m = (hex > 0xFFF) ? 0x1 : 0x11;
	RGB col = {
		(hex >> 0x8*(0x2-(m >> 0x4)) & 0xFF/m)*m,
		(hex >> 0x4*(0x2-(m >> 0x4)) & 0xFF/m)*m,
		(hex >> 0x0*(0x2-(m >> 0x4)) & 0xFF/m)*m
	};
	return col;
}

void setColor(Window *w, const int hex){
	RGB col = hexToRGB(hex);
	w->color = SDL_MapRGB(w->screen->format, col.red, col.green, col.blue);
}

void setAlpha(Window *w, const double alpha){
	w->alpha = alpha;
}

void drawRect(Window *w, const int x, const int y, const int width, const int height){
	SDL_Rect p = {x, y};
	SDL_Surface *r = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0);
	if(r == NULL){
		SDL_ERROR()
	}
	SDL_SetAlpha(r, SDL_SRCALPHA, w->alpha*255);
	SDL_FillRect(r, NULL, w->color); 
	SDL_BlitSurface(r, NULL, w->screen, &p);
	SDL_FreeSurface(r);
}
