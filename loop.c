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
const char txt[] = "So here we are with a great new intro for the masses. Remember: Text mode is not an option, not just a graphics mode. It is a life style. And those of you who think graphical user interfaces are more efficient are stuck in the 90s. This intro uses multithreading and terminal size scalability, adapting banner and scroll text to the current terminal size. Greetings go to all those who love minimalistic computer environments! /Schnitz signing off...  \n";


void loop()
{

	// Set scroll text speed
	delay.tv_sec = 0;  // Seconds delay
	delay.tv_nsec = CYCLETIME; // nsec delay;
	
	int ch;  // ESC input.
	int maxx, maxy, currentmaxy, currentmaxx;  // Terminal size .
	int i;

	const int txtLength = ( sizeof(txt) / sizeof(txt[0])-1 ); // Get length of scroller text.

	// Create text coordinates instance.
	Position coordinates[txtLength];

	while(ch != 27){
	        
		// Don't stop by getch().
		nodelay(stdscr, TRUE);

		// Get terminal size and set window size.
		getmaxyx(stdscr,maxy,maxx);
		if (maxx < 56)  // Set minimal allowed window size.
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
		Bouncer *bounceunit = create_bouncer(7,4);
	
		// Set starting values to all letter coordinates.
		initialize( &maxx, &maxy, &txtLength, coordinates );

		// Character update loop.
		while(currentmaxy == maxy && currentmaxx == maxx && ch != 27){ 
			ch = getch(); // Detect escape button.

			for(i=1;i<=9;i++){
				nanosleep(&delay,NULL);  // Cycle time delay.
				
				// Dotbar and scroller update.
				if(i==1){
					dotbar(&maxx, &maxy, dots);
					scroller(&maxx, &maxy, &txtLength, coordinates);
					print_text(&maxx, &txtLength, coordinates);
				}

				// Only dotbar update.
				else if(i==4||i==7){
					dotbar(&maxx, &maxy, dots);
					print_text(&maxx, &txtLength, coordinates);
				}

				// Move bouncer
				update_bouncer(&maxx, &maxy, bounceunit, &i);

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
