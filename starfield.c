#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "starfield.h"

int getRndNum(int nmbOfTurnouts) // Function to return a random number.
{
	int rand_nbr = (rand()%nmbOfTurnouts+1);
	return rand_nbr;
}

void initializeStars(const int *maxx, const int *maxy, Star *frontstars, Star *middlestars, Star *backstars, const int *nbrOfFrontStars, const int *nbrOfMiddleStars, const int *nbrOfBackStars)
{
	size_t i;
	char square;

	for(i=0;i<*nbrOfFrontStars;i++){
		square = '.';
		while(square == '.'){  // Avoid placing star on another star
			frontstars[i].x = getRndNum(*maxx);
			frontstars[i].y = getRndNum(*maxy/2);
			square = mvinch(frontstars[i].y,frontstars[i].x) & A_CHARTEXT;  // Get square content.
		}
		if(square==' ')
			frontstars[i].bIsVisible = TRUE;
		else
			frontstars[i].bIsVisible = FALSE;
	}
	for(i=0;i<*nbrOfMiddleStars;i++){
		square = '.';
		while(square == '.'){  // Avoid placing star on another star
			middlestars[i].x = getRndNum(*maxx);
			middlestars[i].y = getRndNum(*maxy/2);
			square = mvinch(middlestars[i].y,middlestars[i].x) & A_CHARTEXT;  // Get square content.
		}
		if(square==' ')
			middlestars[i].bIsVisible = TRUE;
		else
			middlestars[i].bIsVisible = FALSE;
	}
	for(i=0;i<*nbrOfBackStars;i++){
		square = '.';
		while(square == '.'){  // Avoid placing star on another star
			backstars[i].x = getRndNum(*maxx);
			backstars[i].y = getRndNum(*maxy/2);
			square = mvinch(backstars[i].y,backstars[i].x) & A_CHARTEXT;  // Get square content.
		}
		if(square==' ')
			backstars[i].bIsVisible = TRUE;
		else
			backstars[i].bIsVisible = FALSE;
	}
}

void area_and_visibility_handling(const int *maxx, const int *maxy, enum direction stardirection, Star *singlestar)
{
	char column;
	chtype columntype;
	// set new position depending on the global direction
	switch(stardirection){
		case STAR_UP:
			if(singlestar->y<1){
				singlestar->y = *maxy/2;
				singlestar->x = getRndNum(*maxx-1);
			}
			break;
		case STAR_UPRIGHT:
			if(singlestar->y<1 || singlestar->x>*maxx){
				if(getRndNum(4)==1){  // choose which axis the star should appear from
					singlestar->y = getRndNum(*maxy/2);
					singlestar->x = 1;
				}
				else{
					singlestar->y = *maxy/2;
					singlestar->x = getRndNum(*maxx-1);
				}
			}
			break;
		case STAR_RIGHT:
			if(singlestar->x>*maxx){
				singlestar->y = getRndNum(*maxy/2);
				singlestar->x = 1;
			}
			break;
		case STAR_DOWNRIGHT:
			if(singlestar->y>*maxy/2 || singlestar->x>*maxx){
				if(getRndNum(4)==1){  // choose which axis the star should appear from
					singlestar->y = getRndNum(*maxy/2);
					singlestar->x = 1;
				}
				else{
					singlestar->y = 1;
					singlestar->x = getRndNum(*maxx-1);
				}
			}
			break;
		case STAR_DOWN:
			if(singlestar->y>*maxy/2){
				singlestar->y = 1;
				singlestar->x = getRndNum(*maxx-1);
			}
			break;
		case STAR_DOWNLEFT:
			if(singlestar->y>*maxy/2 || singlestar->x<1){
				if(getRndNum(4)==1){  // choose which axis the star should appear from
					singlestar->y = 1;
					singlestar->x = getRndNum(*maxx-1);
				}
				else{
					singlestar->y = getRndNum(*maxy/2);
					singlestar->x = getRndNum(*maxx-1);
				}
			}
			break;
		case STAR_LEFT:
			if(singlestar->x<1){
				singlestar->y = getRndNum(*maxy/2);
				singlestar->x = *maxx-1;
			}
			break;
		case STAR_UPLEFT:
			if(singlestar->y<1 || singlestar->x<1){
				if(getRndNum(4)==1){  // choose which axis the star should appear from
					singlestar->y = getRndNum(*maxy/2);
					singlestar->x = *maxx-1;
				}
				else{
					singlestar->y = *maxy/2;
					singlestar->x = getRndNum(*maxx-1);
				}
			}
			break;
		case OVERVALUE:
			stardirection = 0;
		}

	// check new position for characters
	column = mvinch(singlestar->y,singlestar->x) & A_CHARTEXT;
	columntype = mvinch(singlestar->y,singlestar->x);

	// Check column for empty space and absence of bouncer color.
	if(column == ' ' && !(columntype & A_REVERSE))
		singlestar->bIsVisible = TRUE;
	else
		singlestar->bIsVisible = FALSE;
}

void change_star_positions(const int *maxx, const int *maxy, enum direction stardirection, Star *stars, const int *nbrOfStars)
{
	// change direction of array of stars according to the global direction
	size_t i;
	switch(stardirection){
		case STAR_UP:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].y--;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_UPRIGHT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x++;
				stars[i].y--;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_RIGHT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x++;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_DOWNRIGHT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x++;
				stars[i].y++;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_DOWN:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].y++;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_DOWNLEFT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x--;
				stars[i].y++;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_LEFT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x--;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case STAR_UPLEFT:
			for(i=0;i<*nbrOfStars;i++){
				stars[i].x--;
				stars[i].y--;
				area_and_visibility_handling(&*maxx, &*maxy, stardirection, &stars[i]);
			}
			break;
		case OVERVALUE:
			break;
	}
}

void startravel(const int *maxx, const int *maxy, Star *frontstars, Star *middlestars, Star *backstars, const int *nbrOfFrontStars, const int *nbrOfMiddleStars, const int *nbrOfBackStars)
{
	size_t i;
	static int directioncycle = 0;
	static int directionshortcycle = 0;
	static int starturn = 1;
	static enum direction stardirection = STAR_RIGHT;
	chtype columntype;

	// Direction handling.
	directioncycle++;
	if(directioncycle==200 || directioncycle==400 || directioncycle==600 || directioncycle==800 || directioncycle==1000 || directioncycle==1200
			|| directioncycle==1400 || directioncycle>=1600){
		// Restart main star direction cycle.
		if(directioncycle>1900)
			directioncycle = 0;
		// Short cycle mode.
		else if(directioncycle>=1600){
			// Star direction change in short cycle mode.
			if(directionshortcycle>12){
				stardirection++;
				directionshortcycle=0;
			}
			directionshortcycle++;
		}
		// Star direction change in long cycle mode.
		else
			stardirection++;
		// Full circle star direction -> back to first value.
		if(stardirection>STAR_UPLEFT)
			stardirection=STAR_UP;
	}

	// Remove old position stars.
	for(i=0;i<*nbrOfFrontStars;i++){
		if(frontstars[i].bIsVisible)
			mvprintw(frontstars[i].y,frontstars[i].x," ");
	}
	for(i=0;i<*nbrOfMiddleStars;i++){
		if(middlestars[i].bIsVisible)
			mvprintw(middlestars[i].y,middlestars[i].x," ");
	}
	for(i=0;i<*nbrOfBackStars;i++){
		if(backstars[i].bIsVisible)
			mvprintw(backstars[i].y,backstars[i].x," ");
	}

	// 3 cycles and restart to move all 3 star layers.
	if(starturn>3)
		starturn = 1;

	// Move front stars every cycle.
	change_star_positions(&*maxx, &*maxy, stardirection, frontstars, &*nbrOfFrontStars);

	// Move middle stars 2nd and 3rd cycle.
	if(starturn >= 2)
		change_star_positions(&*maxx, &*maxy, stardirection, middlestars, &*nbrOfMiddleStars);

	// Move back stars 3rd cycle.
	if(starturn == 3)
		change_star_positions(&*maxx, &*maxy, stardirection, backstars, &*nbrOfBackStars);

	// Print new position for visible stars.
	for(i=0;i<*nbrOfBackStars;i++){
		if(backstars[i].bIsVisible){
			columntype = mvinch(backstars[i].y,backstars[i].x);
			// Don't use dim or bold when star is printed on a bouncer column.
			if((columntype & A_REVERSE))
				attron(A_DIM);
			mvprintw(backstars[i].y,backstars[i].x,".");
			attroff(A_DIM);
		}
	}
	for(i=0;i<*nbrOfMiddleStars;i++){
		if(middlestars[i].bIsVisible)
			mvprintw(middlestars[i].y,middlestars[i].x,".");
	}
	for(i=0;i<*nbrOfFrontStars;i++){
		if(frontstars[i].bIsVisible){
			columntype = mvinch(backstars[i].y,backstars[i].x);
			// Don't use dim or bold when star is printed on a bouncer column.
			if((columntype & A_REVERSE))
				attron(A_BOLD);
			mvprintw(frontstars[i].y,frontstars[i].x,".");
			attroff(A_BOLD);
		}
	}
	starturn++;
}
