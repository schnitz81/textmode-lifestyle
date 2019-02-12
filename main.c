#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "loop.h"
#include "tune.h"


pthread_t startMultiThread()
{
	int threadRtrn;
	pthread_t  tId;     	
    
	threadRtrn = pthread_create(&tId, NULL, play_music, NULL);  // Second thread call.
	if(threadRtrn){  // If second thread fails - exit.
		endwin();
		printf("\n ERROR: return code from music routine thread is %d \n", threadRtrn);
		exit(1);
	}
	return tId;
}

bool askYesNo(char question[])
{
	char ch;
	int maxx,maxy;
	getmaxyx(stdscr,maxy,maxx);  // Get terminal size.
	mvprintw(maxy/2,(maxx/2)-7,"%s (Y/N)",question);  
	refresh();
	while(true){
		ch=getch();
		if(ch==27){
			// Erase, close current window and exit program. 
			werase(stdscr);
			endwin();	
			exit(0);
		}
		else if(ch=='y'||ch=='Y')
			return TRUE;	
		else if(ch=='n'||ch=='N')
			return FALSE;
	}
}

int main()
{
	// Initialize thread var
	pthread_t threadId;

	// Set screen mode.
	initscr();

	// Disable cursor and user type echoing to screen.
	curs_set(0);
	noecho();
	
	// Get user music choice
	bool music = askYesNo("Music?");

	// Get framcounter choice
	bool framecounter = askYesNo("Framecounter?");

	// Disable output buffer.
	setvbuf(stdout, NULL, _IONBF, 0);
			
	// Start second thread.
	if(music)
		threadId = startMultiThread();

	// Execute loop
	loop(framecounter);
	
	// Shut down music thread and return.
	if(music)
		pthread_cancel(threadId);	

	printf("\n\n\n\n\n Text mode lifestyle.\n\n\n\n\n");
	return 0;
}

