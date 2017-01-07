#include <unistd.h>
#include <mikmod.h>
#include <curses.h>
#include "tune.h"

void *play_music()
{
MODULE *module;

/* register all the drivers */
MikMod_RegisterAllDrivers();

/* register all the module loaders */
MikMod_RegisterAllLoaders();

/* initialize the library */
md_mode |= DMODE_SOFT_MUSIC;
if (MikMod_Init("")) {
	fprintf(stderr, "Could not initialize sound, reason: %s\n",
	MikMod_strerror(MikMod_errno));
	exit(1);
}

/* load module */
module = Player_Load(TUNEFILE, 64, 0);
if (module) {
	/* start module */
	Player_Start(module);
	while (Player_Active()) {
		/* we’re playing */
		usleep(10000);
		MikMod_Update();
	}
	Player_Stop();
	Player_Free(module);
} 
/* give up */
else{
	endwin();
	fprintf(stderr, "Could not load module, reason: %s\n",
	MikMod_strerror(MikMod_errno));
}
MikMod_Exit();
exit(1);
}
