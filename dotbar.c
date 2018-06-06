#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "dotbar.h"
	
	
static int state = 0;

void dotbar(const int *maxx, const int *maxy, dot *dots)
{
	static int counter,bcounter;
	int i;
	static bool cycleskip;

	// Erase last turn dots
	if(state>1){
		for(i=0;i<*maxx;i++)
			mvprintw(dots[i].y,dots[i].x," ");
	}	
	
	// State machine for dotbar's different states.
	switch(state){
		
		case 0:
			counter = 0;
			bcounter = 0;
			cycleskip = FALSE;

			// Initialize all dots.
			for(i=0;i<*maxx;i++){
				dots[i].x = i;
				dots[i].y = *maxy-1;
				dots[i].direction = UP;
				dots[i].visible = FALSE;
			}
			state = 1;
			break;

		case 1:  // Initial pause before first print.
			counter++;
			if(counter==10){   // make longer
				counter = 0;
				state = 2;
			}
			break;
	
		case 2:  // Light all dots from left to right.
			dots[counter].visible = TRUE;
			counter++;
			if(counter>=*maxx){
				counter = 0;
				state = 3;
			}	
			break;
		
		case 3:		// Pause.
			counter++;
			if(counter==50){
				counter = 0;
				state = 4;
			}	
			break;
		
		case 4:  // Put out every other dot.
			for(i=0;i<*maxx;i=i+2)
				dots[i].visible=FALSE;
			state = 5;
			break;
		
		case 5:
			counter++;
			bcounter++;
			if(bcounter==10){		
				// Interwall light half of the dots.
				for(i=0;i<*maxx;i++)
					dots[i].visible = !dots[i].visible;
				bcounter=0;
			}
			if(counter>300){
				counter = 0;
				bcounter = 0;
				state = 6;
			}
			break;
	
		case 6:  // Light all dots.
			for(i=0;i<*maxx;i++)
				dots[i].visible=TRUE;
			state = 7;
			break;
			
		case 7:  // Pause.
			counter++;
			if(counter==50){
				counter = 0;
				state = 8;
			}	
			break;
		
		case 8:  // Straight line motion.
			counter++;
			
			// Update new coordinates.
			for(i=0;i<*maxx;i++){
				if(dots[i].direction==UP)
					dots[i].y--;
				else if(dots[i].direction==DOWN)
					dots[i].y++;
				if(dots[i].y==(*maxy/2)+1)
					dots[i].direction=DOWN;
				else if(dots[i].y==*maxy-1)
					dots[i].direction=UP;
			}
			if(dots[*maxx-1].y == *maxy-1)
				bcounter++;
			
			// Put out every other dot beginning of fourth round.
			if(bcounter==4 && dots[0].y == *maxy-1){
				for(i=0;i<*maxx;i=i+2){
					dots[i].visible=FALSE;	
				}
			}
			
			// Interwall light half of the dots every tenth update.
			if(bcounter >= 4 && (counter%10)==0){
				for(i=0;i<*maxx;i++)
					dots[i].visible = !dots[i].visible;
			}
				
			if(bcounter == 10){
				for(i=0;i<*maxx;i++)
					dots[i].direction=UP;
				counter = 0;
				bcounter = 0;
				state = 9;	
			}
			break;
		
		case 9:  // Pause.
			counter++;
			if(counter==50){
				counter = 0;
				state = 10;
			}	
			break;
			
		case 10:
			switch(cycleskip){
				case TRUE:
					cycleskip=FALSE;
					break;
				case FALSE:
					counter++;
					cycleskip = TRUE;
					// 5-dot width waves
					if(bcounter < *maxx && counter < 150)
						bcounter += 2;
					if(bcounter >=*maxx && counter < 150)
						bcounter = *maxx-1;
	
					// 4-dot width waves
					if(counter == 150)
						bcounter = 0;
				
					if(bcounter < *maxx && counter >= 150 && counter < 300)
						bcounter += 4;
					if(bcounter >=*maxx && counter > 150 && counter < 300)
						bcounter = *maxx-1;
				
					// 3-dot width waves
					if(counter == 300)
						bcounter = 0;
				
					if(bcounter < *maxx && counter >= 300 && counter < 450)
						bcounter += 6;
					if(bcounter >=*maxx && counter > 450 && counter < 450)
						bcounter = *maxx-1;
	
					// 2-dot width waves
					if(counter == 450)
						bcounter = 0;
				
					if(bcounter < *maxx && counter >= 450 && counter < 600)
						bcounter += 8;
					if(bcounter >=*maxx && counter > 450 && counter < 600)
						bcounter = *maxx-1;
				
					// 1-dot width waves
					if(counter == 600)
						bcounter = 0;
				
					if(bcounter < *maxx && counter >= 600 && counter < 750)
						bcounter += 10;
					if(bcounter >=*maxx && counter > 600 && counter < 750)
						bcounter = *maxx-1;
		
					// Update new coordinates.
					for(i=0;i<=bcounter;i++){
						if(dots[i].direction==UP)
							dots[i].y--;
						else if(dots[i].direction==DOWN)
							dots[i].y++;
						if(dots[i].y==(*maxy/2)+1)
							dots[i].direction=DOWN;
						else if(dots[i].y==*maxy-1)
							dots[i].direction=UP;
					}		
					
					// Make invisible from left to right when sequence is done.
					if(counter >= 750 && (counter-750)<*maxx)
						dots[counter-750].visible = FALSE;
			
					// Restart.	
					if((counter - 750) > *maxx)  // If all dots have left the screen.
						state = 0;

					break;
			}  // cycleskip state machine
			break;
	}  // switch  
		
	// Print new dots.
	if(state>1){
		for(i=0;i<*maxx;i++){
			if(dots[i].visible==TRUE)
				mvprintw(dots[i].y,dots[i].x,".");				
		}
	}
}

void restart_dotbar()
{
	// Restart state machine in order to draw a new dotbar.
	state = 0;
}
