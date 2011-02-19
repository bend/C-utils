#define BB_SIZE 10
#include <stdio.h>
#include <stdlib.h>

#include "zip_crack.h"

struct buffer{
char** array;
    char* first;
    char* last;
    unsigned int first_pos;
    unsigned int last_pos;
};
typedef struct buffer buffer;

/*
* Creates a bounded buffer of size  BB_Size
* Each block contains the next String in the dictionary
* @return  buffer : a pointer to the array where the BB will stock the strings 
* A pointer to this  Array is given to the Threads/Process 
*/

buffer* new_bounded_buffer();


/*
* Adds the char* str to the boundedBuffer bb
*
*
*/
void add(buffer *buf,  char* str);

/* removes and return the first added entry in the BB
*/
char* get(buffer *buf);

/*
* Fills the bounded buffer
*/
void fill_bbuffer(buffer *buf);





