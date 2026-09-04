#ifndef STARFIELD_H
#define STARFIELD_H

enum direction { STAR_UP=0, STAR_UPRIGHT, STAR_RIGHT, STAR_DOWNRIGHT, STAR_DOWN, STAR_DOWNLEFT, STAR_LEFT, STAR_UPLEFT, OVERVALUE };

typedef struct star{
	int x;
	int y;
	bool bIsVisible;
} Star;

/* Function prototypes */
int getRndNum(int nmbOfTurnouts);
void initializeStars(const int *maxx, const int *maxy, Star *frontstars, Star *middlestars, Star *backstars, const int *nbrOfFrontStars, const int *nbrOfMiddleStars, const int *nbrOfBackStars);
void area_and_visibility_handling(const int *maxx, const int *maxy, enum direction stardirection, Star *singlestar);
void change_star_positions(const int *maxx, const int *maxy, enum direction stardirection, Star *stars, const int *nbrOfStars);
void startravel(const int *maxx, const int *maxy, Star *frontstars, Star *middlestars, Star *backstars, const int *nbrOfFrontStars, const int *nbrOfMiddleStars, const int *nbrOfBackStars);

#endif
