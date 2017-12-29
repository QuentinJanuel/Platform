#include "window.h"

void startSDL(void){
	if(SDL_Init(SDL_INIT_VIDEO) == -1){
		SDL_ERROR()
	}
}

void closeWindow(Window *w){
	int i = 0;
	for(; i < w->allImages.loaded; i++){
		SDL_FreeSurface(w->allImages.image[i]);
	}
	free(w->allImages.image);
	free(w);
	SDL_Quit();
}

void initializeImages(Window *w, const int max){
	w->allImages.maxNumber = max;
	w->allImages.loaded = 0;
	w->allImages.image = malloc(sizeof(SDL_Surface)*w->allImages.maxNumber);
}

Window *createWindow(const int width, const int height, const char *title, const int FPS){
	startSDL();
	Window *w = malloc(sizeof(*w));
	w->width = width;
	w->height = height;
	w->FPS = FPS;
	w->closed = false;
	w->screen = SDL_SetVideoMode(w->width, w->height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	initializeImages(w, 50);
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

int loadImage(Window *w, const char *file){
	SDL_Surface *img = IMG_Load(file);
	if(img == NULL){
		SDL_ERROR()
	}
	w->allImages.image[w->allImages.loaded] = img;
	return w->allImages.loaded++;
}

void drawImage(Window *w, const int img, const int x, const int y){
	SDL_Rect p = {x, y};
	SDL_SetAlpha(w->allImages.image[img], SDL_SRCALPHA, w->alpha*0xFF);
	SDL_BlitSurface(w->allImages.image[img], NULL, w->screen, &p);
}

void checkForClose(Window *w){
	SDL_Event e = w->events;
	if(e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
		w->closed = true;
}
