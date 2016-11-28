#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bouncer.h"

Bouncer *create_bouncer(const int x, const int y)
{
	Bouncer *unit = malloc(sizeof(Bouncer));
	
	// Store start position for all bouncer pixels.
	
	unit->x = x;
	unit->y = y;
	
	unit->pixels[0].x = x-1;
	unit->pixels[0].y = y-2;
	
	unit->pixels[1].x = x;
	unit->pixels[1].y = y-2;
	
	unit->pixels[2].x = x+1;
	unit->pixels[2].y = y-2;
	
	unit->pixels[3].x = x-3;
	unit->pixels[3].y = y-1;
	
	unit->pixels[4].x = x-2;
	unit->pixels[4].y = y-1;
	
	unit->pixels[5].x = x-1;
	unit->pixels[5].y = y-1;
	
	unit->pixels[6].x = x;
	unit->pixels[6].y = y-1;
	
	unit->pixels[7].x = x+1;
	unit->pixels[7].y = y-1;
	
	unit->pixels[8].x = x+2;
	unit->pixels[8].y = y-1;
	
	unit->pixels[9].x = x+3;
	unit->pixels[9].y = y-1;
	
	unit->pixels[10].x = x-4;
	unit->pixels[10].y = y;
	
	unit->pixels[11].x = x-3;
	unit->pixels[11].y = y;
	
	unit->pixels[12].x = x-2;
	unit->pixels[12].y = y;
	
	unit->pixels[13].x = x-1;
	unit->pixels[13].y = y;
	
	unit->pixels[14].x = x;
	unit->pixels[14].y = y;
	
	unit->pixels[15].x = x+1;
	unit->pixels[15].y = y;
	
	unit->pixels[16].x = x+2;
	unit->pixels[16].y = y;
	
	unit->pixels[17].x = x+3;
	unit->pixels[17].y = y;
	
	unit->pixels[18].x = x+4;
	unit->pixels[18].y = y;
	
	unit->pixels[19].x = x-3;
	unit->pixels[19].y = y+1;
	
	unit->pixels[20].x = x-2;
	unit->pixels[20].y = y+1;

	unit->pixels[21].x = x-1;
	unit->pixels[21].y = y+1;

	unit->pixels[22].x = x;
	unit->pixels[22].y = y+1;

	unit->pixels[23].x = x+1;
	unit->pixels[23].y = y+1;

	unit->pixels[24].x = x+2;
	unit->pixels[24].y = y+1;

	unit->pixels[25].x = x+3;
	unit->pixels[25].y = y+1;
	
	unit->pixels[26].x = x-1;
	unit->pixels[26].y = y+2;
	
	unit->pixels[27].x = x;
	unit->pixels[27].y = y+2;
	
	unit->pixels[28].x = x+1;
	unit->pixels[28].y = y+2;
		
	unit->ydirection = DOWN;
	unit->xdirection = RIGHT;
		
	return unit;	
}

void destroy_bouncer(Bouncer *unit)
{
	free(unit);
} 

void update_bouncer(Bouncer *unit)
{
	// Update all pixels from moved position.
	
	unit->pixels[0].x = unit->x-1;
	unit->pixels[0].y = unit->y-2;
	
	unit->pixels[1].x = unit->x;
	unit->pixels[1].y = unit->y-2;
	
	unit->pixels[2].x = unit->x+1;
	unit->pixels[2].y = unit->y-2;
	
	unit->pixels[3].x = unit->x-3;
	unit->pixels[3].y = unit->y-1;
	
	unit->pixels[4].x = unit->x-2;
	unit->pixels[4].y = unit->y-1;
	
	unit->pixels[5].x = unit->x-1;
	unit->pixels[5].y = unit->y-1;
	
	unit->pixels[6].x = unit->x;
	unit->pixels[6].y = unit->y-1;
	
	unit->pixels[7].x = unit->x+1;
	unit->pixels[7].y = unit->y-1;
	
	unit->pixels[8].x = unit->x+2;
	unit->pixels[8].y = unit->y-1;
	
	unit->pixels[9].x = unit->x+3;
	unit->pixels[9].y = unit->y-1;
	
	unit->pixels[10].x = unit->x-4;
	unit->pixels[10].y = unit->y;
	
	unit->pixels[11].x = unit->x-3;
	unit->pixels[11].y = unit->y;
	
	unit->pixels[12].x = unit->x-2;
	unit->pixels[12].y = unit->y;
	
	unit->pixels[13].x = unit->x-1;
	unit->pixels[13].y = unit->y;
	
	unit->pixels[14].x = unit->x;
	unit->pixels[14].y = unit->y;
	
	unit->pixels[15].x = unit->x+1;
	unit->pixels[15].y = unit->y;
	
	unit->pixels[16].x = unit->x+2;
	unit->pixels[16].y = unit->y;
	
	unit->pixels[17].x = unit->x+3;
	unit->pixels[17].y = unit->y;
	
	unit->pixels[18].x = unit->x+4;
	unit->pixels[18].y = unit->y;
	
	unit->pixels[19].x = unit->x-3;
	unit->pixels[19].y = unit->y+1;
	
	unit->pixels[20].x = unit->x-2;
	unit->pixels[20].y = unit->y+1;

	unit->pixels[21].x = unit->x-1;
	unit->pixels[21].y = unit->y+1;

	unit->pixels[22].x = unit->x;
	unit->pixels[22].y = unit->y+1;

	unit->pixels[23].x = unit->x+1;
	unit->pixels[23].y = unit->y+1;

	unit->pixels[24].x = unit->x+2;
	unit->pixels[24].y = unit->y+1;

	unit->pixels[25].x = unit->x+3;
	unit->pixels[25].y = unit->y+1;
	
	unit->pixels[26].x = unit->x-1;
	unit->pixels[26].y = unit->y+2;
	
	unit->pixels[27].x = unit->x;
	unit->pixels[27].y = unit->y+2;
	
	unit->pixels[28].x = unit->x+1;
	unit->pixels[28].y = unit->y+2;
}

void erase_old_bouncer(Bouncer *unit)
{
	int i;
	chtype tmppixel;
	for(i=0;i<=28;i++){
		tmppixel = mvinch(unit->pixels[i].y,unit->pixels[i].x);
		tmppixel -= (tmppixel & A_STANDOUT);
		mvaddch(unit->pixels[i].y,unit->pixels[i].x,tmppixel);
	}
}

void print_bouncer(Bouncer *unit)
{
	int i;
	chtype tmppixel;
	attron(A_STANDOUT); 
	for(i=0;i<=28;i++){  // Draw bouncer by inverting.
		tmppixel = mvinch(unit->pixels[i].y,unit->pixels[i].x);
		mvaddch(unit->pixels[i].y,unit->pixels[i].x,tmppixel);
	}
	attroff(A_STANDOUT);
}

void move_bouncer(const int *maxx, const int *maxy, Bouncer *unit)
{
	erase_old_bouncer(unit);
	
	// *** Bouncer movement logic ***
	
	// Y-wise movement.
	if(unit->ydirection == DOWN )
		unit->y++;
	else if(unit->ydirection == UP )
		unit->y--;

	// X-wise movement
	if(unit->xdirection == RIGHT && unit->y == *maxy/4)
		unit->x++;
	else if(unit->xdirection == LEFT && unit->y == *maxy/4)
		unit->x--;	
	
	// Floor is hit.
	if(unit->y+2 >= (*maxy/2)-1)
		unit->ydirection = UP;
	// Top is reached.
	else if(unit->y-2 <= 1)
		unit->ydirection = DOWN;
	
	// Wall is hit
	if(unit->x + 5 >= *maxx-1)
		unit->xdirection = LEFT;
	else if(unit->x - 4 <= 1)
		unit->xdirection = RIGHT;
	
	update_bouncer(unit);
	print_bouncer(unit);
}
