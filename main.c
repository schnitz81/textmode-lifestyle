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

int main()
{
	// Disable output buffer.
	setvbuf(stdout, NULL, _IONBF, 0);
			
	// Start second thread.
	pthread_t threadId = startMultiThread();

	// Execute loop
	loop();
	
	// Shut down music thread and return .
	pthread_cancel(threadId);	
	
	printf("\n\n\n\n\n Text mode lifestyle.\n\n\n\n\n");
	return 0;
}

