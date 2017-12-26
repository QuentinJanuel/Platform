#include "keyboard.h"

void getKey(bool *state, const SDL_Event e, const SDLKey which){
	if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
		if(e.key.keysym.sym == which){
			*state = (e.type == SDL_KEYDOWN) ? true : false;
		}
	}
}
