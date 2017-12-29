#include "standart.h"

bool sign(const int x){
	return (x > 0)-(x < 0);
}

void swap(int *a, int *b){
	*a += *b;
	*b = *a-*b;
	*a -= *b;
}
