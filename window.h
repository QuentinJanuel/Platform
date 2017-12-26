#ifndef WINDOW
#define WINDOW

#include <SDL_image.h>

#define SDL_ERROR()	fprintf(stderr, "Error: %s\n", SDL_GetError()); \
					exit(EXIT_FAILURE);

typedef struct Images{
	int maxNumber;
	int loaded;
	SDL_Surface **image;
} Images;

typedef struct Window{
	SDL_Surface *screen;
	Uint32 color;
	int width;
	int height;
	int FPS;
	unsigned int pTime;
	double alpha;
	Images allImages;
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

void initializeImages(Window*, const int);

Window *createWindow(const int, const int, const char*, const int);

void screenClear(Window*);

void drawRect(Window*, const int, const int, const int, const int);

int loadImage(Window*, const char*);

void drawImage(Window*, const int, const int, const int);

#endif //WINDOW