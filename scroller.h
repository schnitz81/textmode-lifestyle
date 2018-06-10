#ifndef SCROLLER_H
#define SCROLLER_H

typedef enum downOrUp { DOWN, UP } downOrUp;

typedef struct {
	int x;
	int y;
	downOrUp direction;
	int dirDuration;
} Position;


/* Function prototypes */
void initialize( const int *maxx, const int *maxy, const int *txtLength, Position *coordinates );
void scroller(const int *maxx, const int *maxy, const int *txtLength, Position *coordinates);
void print_text(const int *maxx, const int *txtLength, const Position *coordinates);


#endif

