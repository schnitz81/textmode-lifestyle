#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "banner.h"
#include "bouncer.h"
#include "loop.h"
#include "scroller.h"
#include "dotbar.h"

/* Scroll text */
const char txt[] = "So here we are with a great new intro for the masses. Remember: Text mode is not an option, not just a graphics mode. It is a life style. And those of you who think graphical user interfaces are more efficient are stuck in the 90s. This intro uses multithreading and terminal size scalability, adapting banner and scroll text to the terminal size at launch. Greetings go to all those who love minimalistic computer environments! /Schnitz signing off...  \n";


void loop()
{

	// Set scroll text speed
	delay.tv_sec = 0;  // Seconds delay
	delay.tv_nsec=11000000;  // nsec delay;
	int ch;  // ESC input.
	int maxx, maxy, currentmaxy, currentmaxx;  // Terminal size .
	int i;

	const int txtLength = ( sizeof(txt) / sizeof(txt[0])-1 ); // Get length of scroller text.

	// Create text coordinates instance.
	Position coordinates[txtLength];

	while(ch != 27){
	        
		// Set screen mode.
        	initscr();

	        // Don't stop by getch().
	        nodelay(stdscr, TRUE);

	        // Disable cursor.
	        curs_set(0);

	
	        // Get terminal size and set window size.
		getmaxyx(stdscr,maxy,maxx);
		if (maxx < 56)
			maxx = 56;
		if (maxy < 23)
			maxy = 23;
		currentmaxy = maxy;
		currentmaxx = maxx;

		// Create dotbar instance.
		dot dots[maxx-1];
	
		// Print banner
		banner( &maxx, &maxy );	
	
		// Initialize bouncer object.
		Bouncer *bounceunit = create_bouncer( 7, 4 );
	
		// Set starting values to all letter coordinates.
		initialize( &maxx, &maxy, &txtLength, coordinates );


		// Character update loop.
		while(currentmaxy == maxy && currentmaxx == maxx && ch != 27){ 
			ch = getch(); // Detect escape button.
		
			for(i=1;i<=9;i++){
				nanosleep(&delay,NULL);
				if(i==1){
					dotbar( &maxx, &maxy, dots);
					scroller(&maxx, &maxy, &txtLength, coordinates);
				}
				else if(i==4){
					dotbar( &maxx, &maxy, dots);
					print_text(&maxx, &txtLength, coordinates);
				}
				else if(i==7){
					dotbar( &maxx, &maxy, dots);	
					print_text(&maxx, &txtLength, coordinates);
				}
			
				// Gravitational bounce movement.
				if(maxy > 40){  // Large terminal window.
					if((bounceunit->y) > ((maxy/2)/10)*9)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*8 && i<9)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*7 && i<8)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*6 && i<7)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*5 && i<6)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*4 && i<5)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*3 && i<4)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*2 && i<3)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/10)*1 && i<2)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) <= ((maxy/2)/10)*1 && i<2)
						move_bouncer(&maxx, &maxy, bounceunit);
				}
				else{  // Minimal terminal window.
					if((bounceunit->y) > ((maxy/2)/5)*5 && i<5)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/5)*4 && i<5)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/5)*3 && i<4)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/5)*2 && i<3)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) > ((maxy/2)/5)*1 && i<2)
						move_bouncer(&maxx, &maxy, bounceunit);
					else if((bounceunit->y) <= ((maxy/2)/5)*1 && i<2)
						move_bouncer(&maxx, &maxy, bounceunit);
				}
				refresh();
				fflush(stdout);
			}
			// Check for new window size.
	                getmaxyx(stdscr,currentmaxy,currentmaxx);
		}  // while

		/* In case of window resize or ESC pressed. */

		// Remove bouncer and restart dotbar.
		destroy_bouncer(bounceunit);
		restart_dotbar();

		// Erase and close current window. 
		werase(stdscr);
	        endwin();

	} // while
}
