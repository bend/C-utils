#ifndef __BOUNDED_BUFFER_H__
#define __BOUNDED_BUFFER_H__

#define BUFFER_FULL -1;
#define BUFFER_SUCCESS 0;

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "zip_crack.h"

struct buffer{
	char** array;
    unsigned int first_pos;
    unsigned int last_pos;
	unsigned int nb_elem;
	unsigned int size;
	char* name;
	pthread_mutex_t *mutex;
};
typedef struct buffer buffer;

/*
* Creates a bounded buffer of size size
* @return  buffer : a pointer to the struct bounded buffer
*/
buffer* bounded_buffer_new(unsigned int size);


/*
* Adds the char* str to the boundedBuffer bb
* Returns 0 if item successfuly added
* Returns -1 if failed i.e. the buffer is full
*/
int bounded_buffer_put(buffer *buf,  char* str);

/* 
* Removes and return the first added entry in the buffer
* returns NULL if buffer empty
* @param buf the buffer
*/
char* bounded_buffer_get(buffer *buf);

/*
* Frees the allocalted mem for the buffer
* Frees also each char* in it
*/
void bounded_buffer_free(buffer *buf);



#endif


