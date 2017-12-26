#include "player.h"

Player newPlayer(Window *w, const int x, const int y){
	Player p = {x, y};
	p.color = 0x0A0;
	p.width = 18;
	p.height = 25;
	p.spd = 3;
	p.hspd = 0;
	p.vspd = 0;
	p.gravity = 0.4;
	p.jump = 8;
	p.maxVspd = 9;
	p.tJump = 0.4;
	p.canJump = true;
	p.sprite = 0;
	p.mirror = false;
	p.imgIndex = 0;
	p.img[0] = loadImage(w, "images/mario01.png");
	p.img[1] = loadImage(w, "images/mario02.png");
	p.img[2] = loadImage(w, "images/mario03.png");
	p.img[3] = loadImage(w, "images/mario04.png");
	p.img[4] = loadImage(w, "images/mario05.png");
	p.img[5] = loadImage(w, "images/mario06.png");
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
	p->sprite = 2;
	p->hspd = p->spd*(key.right-key.left);
	if(collidePlayerBlocks(p->x+p->hspd, p->y, *p, blocks)){
		while(!collidePlayerBlocks(p->x+sign(p->hspd), p->y, *p, blocks))
			p->x += sign(p->hspd);
		p->hspd = 0;
	}
	p->x += p->hspd;
	p->vspd += p->gravity;
	if(p->vspd > p->maxVspd)
		p->vspd = p->maxVspd;
	p->canJump = (collidePlayerBlocks(p->x, p->y+1, *p, blocks)) ? true : false;
	if(p->canJump){
		if(key.up && !key.preUp)
			p->vspd = -p->jump;
		else
			p->sprite = (p->hspd == 0) ? 0 : p->imgIndex/4%2;
	}
	if(!key.up && p->vspd < 0)
		p->vspd *= p->tJump;
	if(collidePlayerBlocks(p->x, p->y+p->vspd, *p, blocks)){
		while(!collidePlayerBlocks(p->x, p->y+sign(p->vspd), *p, blocks))
			p->y += sign(p->vspd);
		p->vspd = 0;
	}
	p->y += p->vspd;
	p->mirror = (p->hspd < 0) ? true : p->mirror;
	p->mirror = (p->hspd > 0) ? false : p->mirror;
	p->imgIndex++;
}

void drawPlayer(Window *w, const Player p){
	setColor(w, p.color);
	drawImage(w, p.img[p.sprite+3*p.mirror], p.x-25, p.y-22);
}
