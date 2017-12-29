#ifndef KEYBOARD
#define KEYBOARD

#include <bool.h>
#include <SDL.h>
#include "window.h"

typedef struct Keyboard{
	bool up;
	bool preUp;
	bool left;
	bool right;
} Keyboard;

void getKey(const SDL_Event, bool*, const SDLKey);

void handleKeyboard(Window*, Keyboard*);

#endif //KEYBOARD