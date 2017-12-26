#include "player.h"

Player newPlayer(const int x, const int y){
	Player p = {x, y};
	p.color = 0x0A0;
	p.width = 14;
	p.height = 20;
	p.spd = 3;
	p.hspd = 0;
	p.vspd = 0;
	p.gravity = 0.4;
	p.jump = 8;
	p.maxVspd = 9;
	p.tJump = 0.4;
	p.canJump = true;
	return p;
}

bool collidePlayerBlocks(const int x, const int y, const Player p, const Blocks blocks){
	int i = 0;
	Block b;
	for(; i < blocks.number; i++){
		b = blocks.b[i];
		if(collide(x, y, p.width, p.height, b.x, b.y, b.width, b.height)){
			return true;
		}
	}
	return false;
}

void updatePlayer(const Keyboard key, Player *p, const Blocks blocks){
	//X
	p->hspd = p->spd*(key.right-key.left);
	if(collidePlayerBlocks(p->x+p->hspd, p->y, *p, blocks)){
		while(!collidePlayerBlocks(p->x+sign(p->hspd), p->y, *p, blocks))
			p->x += sign(p->hspd);
		p->hspd = 0;
	}
	p->x += p->hspd;

	//Y
	p->vspd += p->gravity;
	if(p->vspd > p->maxVspd)
		p->vspd = p->maxVspd;
	p->canJump = (collidePlayerBlocks(p->x, p->y+1, *p, blocks)) ? true : false;
	if(key.up && !key.preUp && p->canJump)
		p->vspd = -p->jump;
	if(!key.up && p->vspd < 0)
		p->vspd *= p->tJump;
	if(collidePlayerBlocks(p->x, p->y+p->vspd, *p, blocks)){
		while(!collidePlayerBlocks(p->x, p->y+sign(p->vspd), *p, blocks))
			p->y += sign(p->vspd);
		p->vspd = 0;
	}
	p->y += p->vspd;
}

void drawPlayer(Window *w, const Player p){
	setColor(w, p.color);
	drawRect(w, p.x, p.y, p.width, p.height);
}
