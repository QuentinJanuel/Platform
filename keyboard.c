#include "keyboard.h"

void getKey( const SDL_Event e, bool *state, const SDLKey which){
	if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
		if(e.key.keysym.sym == which){
			*state = (e.type == SDL_KEYDOWN) ? true : false;
		}
	}
}

void handleKeyboard(Window *w, Keyboard *k){
	SDL_Event e = w->events;
	k->preUp = k->up;
	getKey(e, &k->up, SDLK_UP);
	getKey(e, &k->left, SDLK_LEFT);
	getKey(e, &k->right, SDLK_RIGHT);
}
