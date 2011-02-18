#include "zip_crack.h"
#define BB_SIZE


/*
* Creates a bounded buffer of size  BB_Size
* Each block contains the next String in the dictionary
* @return  buffer : a pointer to the array where the BB will stock the strings 
* A pointer to this  Array is given to the Threads/Process 
*/

char** new_bounded_buffer();


/*
* Adds the char* str to the boundedBuffer bb
*
*
*/
void add(char** bb, char* str);


void get(char** bb);



/*
* Stats the cracking routine, by creating N Threads/proc
*/

void begin(unsigned int nbThreads);



