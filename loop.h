#ifndef LOOP_H
#define LOOP_H

extern const char txt[];

#define CYCLETIME 10800000  // Cycletime.
struct timespec delay; // Data type for pause timer.

/* Function prototypes */
void loop(bool framecounter);


#endif

