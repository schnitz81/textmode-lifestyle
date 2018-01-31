#ifndef BOUNCER_H
#define BOUNCER_H

#include "scroller.h"

typedef enum leftOrRight { LEFT, RIGHT } leftOrRight;

typedef struct pixel{
	int x;
	int y;	
} Pixel; 

typedef struct bouncer {
	int x;
	int y;
	Pixel pixels[29];
	downOrUp ydirection;
	leftOrRight xdirection;
} Bouncer;

/* Function prototypes */
Bouncer *create_bouncer(const int x, const int y);
void destroy_bouncer(Bouncer *unit);
void update_bouncer_pixels(Bouncer *unit);
void update_bouncer(const int *maxx, const int *maxy, Bouncer *unit, const int *i);
int evaluate_bouncer_movement_round(const int *maxy, Bouncer *unit, const int *i);

#endif
