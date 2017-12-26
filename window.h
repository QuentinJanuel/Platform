#ifndef WINDOW
#define WINDOW

#include <SDL.h>

#define SDL_ERROR()	fprintf(stderr, "Error: %s\n", SDL_GetError()); \
					exit(EXIT_FAILURE);

typedef struct Window{
	SDL_Surface *screen;
	Uint32 color;
	int width;
	int height;
	int FPS;
	unsigned int pTime;
	double alpha;
} Window;

typedef struct RGB{
	int red;
	int green;
	int blue;
} RGB;

RGB hexToRGB(int hex);

void setColor(Window*, const int);

void setAlpha(Window*, const double);

void startSDL(void);

void endSDL(Window *w);

Window *createWindow(const int, const int, const char*, const int);

void screenClear(Window*);

void drawRect(Window*, const int, const int, const int, const int);

#endif //WINDOW