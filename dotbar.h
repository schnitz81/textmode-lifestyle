#ifndef DOTBAR_H
#define DOTBAR_H

#include "scroller.h" // Included for the downOrUp data type.

typedef struct {
	int x;
	int y;
	downOrUp direction;
	bool visible;
} dot;

/* Function prototypes */
void dotbar(const int *maxx, const int *maxy, dot *dots);


#endif

