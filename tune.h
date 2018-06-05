#ifndef TUNE_H
#define TUNE_H


/* Set tune path to shared folder if compiled as a package with PACKAGE macro.  */
#ifdef PACKAGE
#define TUNEFILE "/usr/share/textmode-lifestyle/tune.dat"	
#else
#define TUNEFILE "tune.dat"
#endif


/* Function prototypes */
void *play_music();


#endif
