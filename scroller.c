#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "scroller.h"
#include "loop.h"
#include "dotbar.h"


void initialize( const int *maxx, const int *maxy, const int *txtLength, Position *coordinates )
{
	int i;
	// Initiate coordinate arrays.
	for(i=0;i<=*txtLength;++i){ 
		coordinates[i].x = (*maxx+1)+i;
		coordinates[i].y = (*maxy/2)+2;
		coordinates[i].direction = DOWN;
		coordinates[i].dirDuration = 0;
	}
}

void scroller(const int *maxx, const int *maxy, const int *txtLength, Position *coordinates)
{
	int i,j;  // For-loop variables.

	// Erase text (doesn't change until next refresh)
	for(i=0;i<=*txtLength;i++){
		if( coordinates[i].x >= 0 && coordinates[i].x < *maxx )  // Only if position is a positive coordinate.
			mvprintw( coordinates[i].y,coordinates[i].x," " );  // Erase.		
	}

	// Update all coordinates.
	for(i=0;i<=*txtLength;i++){   

		// One step left.
		coordinates[i].x--;	
			
		// If letter has entered screen area.
		if(coordinates[i].x <= *maxx-1){  
			
			// Count up how long a letter has been on the same Y-axis course.
			coordinates[i].dirDuration++;
			
			// Move y-axis depending on present direction.
			if(coordinates[i].direction == DOWN)
				coordinates[i].y++;
			else if(coordinates[i].direction == UP)
				coordinates[i].y--;
				
			// Change direction at outer limits.
			if(coordinates[i].y >= *maxy-1){
				coordinates[i].direction = UP;
				coordinates[i].dirDuration = 0;
			}
			else if(coordinates[i].y <= (*maxy/2)+1){
				coordinates[i].direction = DOWN;
				coordinates[i].dirDuration = 0;
			}
			
			// waggle motion
			if(coordinates[i].dirDuration==5){
				coordinates[i].direction = !coordinates[i].direction;
			}
			else if(coordinates[i].dirDuration==8){
				coordinates[i].dirDuration = 0;
				coordinates[i].direction = !coordinates[i].direction;
			}
		} 
			
		// If entering letter is space, adjust the rest both Y- and X-axis wise.
		if(coordinates[i].x == *maxx-1 && txt[i] == ' ' && coordinates[i].direction == DOWN ){
			for(j=i;j<=*txtLength;j++){
				coordinates[j].y++;
				if(j>i)
					coordinates[j].x += 5;  
			}
		}      
		else if( coordinates[i].x == *maxx-1 && txt[i] == ' ' && coordinates[i].direction == UP ){
			for(j=i;j<=*txtLength;j++){
				coordinates[j].y--;
				if(j>i)
					coordinates[j].x += 5;  
			}
		}	
			
		// Change entering Y-coordinate + direction at outer limits.
		if(coordinates[i].x == *maxx-1 && coordinates[i].y >= *maxy-1){
			for(j=i;j<=*txtLength;j++)
				coordinates[j].direction = UP;
		}
		else if(coordinates[i].x == *maxx-1 && coordinates[i].y == (*maxy/2)+1){
			for(j=i;j<=*txtLength;j++)
				coordinates[j].direction = DOWN;
		}
	} // for
		
	// Reinitialize all coordinates if all text have scrolled past the screen.
	if(coordinates[*txtLength].x < 0){
		initialize( &*maxx, &*maxy, &*txtLength, coordinates );
	}
}

void print_text(const int *maxx, const int *txtLength, const Position *coordinates)
{
	int i;
	
	// Print out text.
	for(i=0;i<=*txtLength;i++){
		if( coordinates[i].x >= 0 && coordinates[i].x < *maxx )  // Only if position is "inscreen".
			mvprintw(coordinates[i].y,coordinates[i].x,"%c",txt[i]); 
	}
}
