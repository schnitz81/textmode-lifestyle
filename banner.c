#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "banner.h"

void banner(const int *maxx, const int *maxy)
{
	int i;
	int posx, posy;
	enum threesizes bannerchoice;

	// Draw middle separator
	for(i=0;i<*maxx;i++)
		mvprintw(*maxy/2,i,"%c",35);
	
	// Upper frame left edge.
	mvprintw(0,1,"/"); 
		
	// upper frame
	for(i=2;i<*maxx-2;i++) 
		mvprintw(0,i,"|");

	// Upper frame right edge.
	mvprintw(0,*maxx-2,"\\");

	// left frame
	for(i=1;i<*maxy/2;i++)
		mvprintw(i,0,"/");

	// right frame
	for(i=1;i<*maxy/2;i++) 
		mvprintw(i,*maxx-1,"\\");

	// Choose banner by terminal size.
	if(*maxy<=33){
		bannerchoice = SMALL;
		posx = *maxx/2 - 27;
		posy = *maxy/4 - 3;
	}
	else if(*maxx<=112 || *maxy<=48){
		bannerchoice = MEDIUM;
		posx = *maxx/2 - 27;
		posy = *maxy/4 - 7;
	}
	else if(*maxx>112 && *maxy>48){
		bannerchoice = LARGE;
		posx = *maxx/2 - 55;
		posy = *maxy/4 - 10;
	}
	else{
		endwin();
		printf("\nERROR: Something went horribly wrong.\n");
		exit(1);
	}

	switch (bannerchoice){
		case SMALL:
			move(posy,posx);
			printw(" ____  ____  _  _  ____    __  __  _____  ____  ____ ");
			move(posy+1,posx);
			printw("(_  _)( ___)( \\/ )(_  _)  (  \\/  )(  _  )(  _ \\( ___)");
			move(posy+2,posx);
			printw("  )(   )__)  )  (   )(     )    (  )(_)(  )(_) ))__) ");
			move(posy+3,posx);
			printw(" (__) (____)(_/\\_) (__)   (_/\\/\\_)(_____)(____/(____)");
			move(posy+4,posx);
			printw(" __    ____  ____  ____  ___  ____  _  _  __    ____ ");
			move(posy+5,posx);
			printw("(  )  (_  _)( ___)( ___)/ __)(_  _)( \\/ )(  )  ( ___)");
			move(posy+6,posx);
			printw(" )(__  _)(_  )__)  )__) \\__ \\  )(   \\  /  )(__  )__) ");
			move(posy+7,posx);
			printw("(____)(____)(__)  (____)(___/ (__)  (__) (____)(____)");
			break;
		case MEDIUM:
			move(posy,posx);
			printw("                )             *        )  (           ");
			move(posy+1,posx);
			printw("  *   )      ( /(   *   )   (  `    ( /(  )\\ )        ");
			move(posy+2,posx);
			printw("` )  /( (    )\\())` )  /(   )\\))(   )\\())(()/(   (    ");
			move(posy+3,posx);
			printw(" ( )(_)))\\  ((_)\\  ( )(_)) ((_)()\\ ((_)\\  /(_))  )\\   ");
			move(posy+4,posx);
			printw("(_(_())((_) __((_)(_(_())  (_()((_)  ((_)(_))_  ((_)  ");
			move(posy+5,posx);
			printw("|_   _|| __|\\ \\/ /|_   _|  |  \\/  | / _ \\ |   \\ | __| ");
			move(posy+6,posx);
			printw("  | |  | _|  >  <   | |    | |\\/| || (_) || |) || _|  ");
			move(posy+7,posx);
			printw(" (|_|  (___|(_/\\_\\  |_|(   |_|  |_| \\__)/ (___/ |___| ");
			move(posy+8,posx);
			printw(" )\\ )  )\\ ) )\\ )       )\\ )  *   )  ( /(  )\\ )        ");
			move(posy+9,posx);
			printw("(()/( (()/((()/(  (   (()/(` )  /(  )\\())(()/(  (     ");
			move(posy+10,posx);
			printw(" /(_)) /(_))/(_)) )\\   /(_))( )(_))((_)\\  /(_)) )\\    ");
			move(posy+11,posx);
			printw("(_))  (_)) (_))_|((_) (_)) (_(_())__ ((_)(_))  ((_)   ");
			move(posy+12,posx);
			printw("| |   |_ _|| |_  | __|/ __||_   _|\\ \\ / /| |   | __|  ");
			move(posy+13,posx);
			printw("| |__  | | | __| | _| \\__ \\  | |   \\ V / | |__ | _|   ");
			move(posy+14,posx);
			printw("|____||___||_|   |___||___/  |_|    |_|  |____||___|  ");
			break;
		case LARGE:
			move(posy,posx);
			printw("                   ___          __                             ___          ___          ___          ___  ");
			move(posy+1,posx);
			printw("      ___         /  /\\        |  |\\     ___                  /  /\\        /  /\\        /  /\\        /  /\\ ");
			move(posy+2,posx);
			printw("     /__/\\       /  /::\\       |  |:|   /__/\\                /  /::|      /  /::\\      /  /::\\      /  /::\\ ");
			move(posy+3,posx);
			printw("     \\  \\:\\     /  /:/\\:\\      |  |:|   \\  \\:\\              /  /:|:|     /  /:/\\:\\    /  /:/\\:\\    /  /:/\\:\\ ");
			move(posy+4,posx);
			printw("      \\__\\:\\   /  /::\\ \\:\\     |__|:|__  \\__\\:\\            /  /:/|:|__  /  /:/  \\:\\  /  /:/  \\:\\  /  /::\\ \\:\\ ");
			move(posy+5,posx);
			printw("      /  /::\\ /__/:/\\:\\ \\:\\____/__/::::\\ /  /::\\          /__/:/_|::::\\/__/:/ \\__\\:\\/__/:/ \\__\\:|/__/:/\\:\\ \\:\\");
			move(posy+6,posx);
			printw("     /  /:/\\:\\\\  \\:\\ \\:\\_\\/\\__\\::::/----/  /:/\\:\\         \\__\\/  /--/:/\\  \\:\\ /  /:/\\  \\:\\ /  /:/\\  \\:\\ \\:\\_\\/ ");
			move(posy+7,posx);
			printw("    /  /:/\\_\\/ \\  \\:\\ \\:\\     |--|:|   /  /:/\\_\\/               /  /:/  \\  \\:\\  /:/  \\  \\:\\  /:/  \\  \\:\\ \\:\\ ");
			move(posy+8,posx);
			printw("   /__/:/       \\  \\:\\_\\/     |  |:|  /__/:/                   /  /:/    \\  \\:\\/:/    \\  \\:\\/:/    \\  \\:\\_\\/ ");
			move(posy+9,posx);
			printw("   \\__\\/         \\  \\:\\       |__|:|  \\__\\/                   /__/:/      \\  \\::/      \\__\\__/      \\  \\:\\ ");
			move(posy+10,posx);
			printw("                  \\__\\/        \\__\\|                          \\__\\/        \\__\\/                     \\__\\/ ");
			move(posy+11,posx);
			printw("      ___                           ___          ___                             ___      ___  ");
			move(posy+12,posx);
			printw("     /  /\\   ___       ___         /  /\\        /  /\\     ___       __          /  /\\    /  /\\  ");
			move(posy+13,posx);
			printw("    /  /:/  /__/\\     /  /\\       /  /::\\      /  /::\\   /__/\\     |  |\\       /  /:/   /  /::\\ ");
			move(posy+14,posx);
			printw("   /  /:/   \\__\\:\\   /  /::\\     /  /:/\\:\\    /__/:/\\:\\  \\  \\:\\    |  |:|     /  /:/   /  /:/\\:\\  ");
			move(posy+15,posx);
			printw("  /  /:/    /  /::\\ /  /:/\\:\\   /  /::\\ \\:\\  _\\_ \\:\\ \\:\\  \\__\\:\\   |  |:|    /  /:/   /  /::\\ \\:\\ ");
			move(posy+16,posx);
			printw(" /__/:/  __/  /:/\\//  /::\\ \\:\\ /__/:/\\:\\ \\:\\/__/\\ \\:\\ \\:\\ /  /::\\  |__|:|__ /__/:/   /__/:/\\:\\ \\:\\  ");
			move(posy+17,posx);
			printw(" \\  \\:\\ /__/\\/:/--/__/:/\\:\\ \\:\\\\  \\:\\ \\:\\_\\/\\  \\:\\ \\:\\_\\//  /:/\\:\\ /  /::::\\\\  \\:\\   \\  \\:\\ \\:\\_\\/ ");
			move(posy+18,posx);
			printw("  \\  \\:\\\\  \\::/   \\__\\/  \\:\\_\\/ \\  \\:\\ \\:\\   \\  \\:\\_\\:\\ /  /:/\\_\\//  /:/---- \\  \\:\\   \\  \\:\\ \\:\\ ");
			move(posy+19,posx);
			printw("   \\  \\:\\\\  \\:\\        \\  \\:\\    \\  \\:\\_\\/    \\  \\:\\/://__/:/    /__/:/       \\  \\:\\   \\  \\:\\_\\/ ");
			move(posy+20,posx);
			printw("    \\  \\:\\\\__\\/         \\__\\/     \\  \\:\\       \\  \\::/ \\__\\/     \\__\\/         \\  \\:\\   \\  \\:\\ ");
			move(posy+21,posx);
			printw("     \\__\\/                         \\__\\/        \\__\\/                           \\__\\/    \\__\\/ ");
			break;
		default:  // Should never happen.
			break;
	}
	mvprintw(1,*maxx-12,"by schnitz");
}
