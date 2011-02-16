#include "zip_crack.h"
#define BB_SIZE


/*
* Creates a bounded buffer of size  BB_Size
* Each block contains the next String in the dictionary
* @param buffer : a pointer to the array where the BB will stock the strings 
* A pointer to this  Array is given to the Threads/Process 
*/

void startBoundedBuffer(char** buffer);

/*
* Stats the cracking routine, by creating N Threads/proc
*/

void begin(unsigned int nbThreads);


