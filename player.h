#ifndef PLAYER
#define PLAYER

#include <bool.h>
#include "window.h"
#include "keyboard.h"
#include "block.h"
#include "collision.h"
#include "standart.h"

typedef struct Player{
	int x;
	int y;
	int color;
	int width;
	int height;
	int spd;
	int hspd;
	double vspd;
	double gravity;
	int jump;
	int maxVspd;
	double tJump;
	bool canJump;
} Player;

Player newPlayer(const int, const int);

bool collidePlayerBlocks(const int, const int, const Player, const Blocks);

void updatePlayer(const Keyboard, Player*, const Blocks);

void drawPlayer(Window*, const Player);

#endif //PLAYER