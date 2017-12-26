#ifndef KEYBOARD
#define KEYBOARD

#include <bool.h>
#include <SDL.h>

typedef struct Keyboard{
	bool up;
	bool preUp;
	bool left;
	bool right;
} Keyboard;

void getKey(bool*, const SDL_Event, const SDLKey);

#endif //KEYBOARD