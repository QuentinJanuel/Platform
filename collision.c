#include "collision.h"

bool collide(const int x1, const int y1, const int w1, const int h1, const int x2, const int y2, const int w2, const int h2){
	bool xCol = x1+w1 > x2 && x1 < x2+w2;
	bool yCol = y1+h1 > y2 && y1 < y2+h2;
	if(xCol && yCol){
		return true;
	}else{
		return false;
	}
}
