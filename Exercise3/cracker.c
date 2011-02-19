#include "cracker.h"
#include "file_reader.h"




buffer*  new_bounded_buffer(){
	buffer *buf;

	buf = malloc(sizeof(buffer));
	if(buf == NULL){
		perror("Error in malloc");
		exit(-1);
	}
	buf->array = malloc(sizeof(char*)*BB_SIZE);
	if(buf->array == NULL){
		free(buf);
		perror("malloc error");
		exit(-1);
	}
	return buf;
}


void  fill_bbuffer(buffer *buf){
	int i;
	FILE *file;
	char* path= "tests/tests.txt";
	char* t;

	i=0;
	file = open_file(path);					/* Open file 		*/
	t=get_next(file);
	while(t!=NULL && i<BB_SIZE){				/* fill buffer */
		buf->array[i++] = t;
		t=get_next(file);
	}
	buf->first_pos = 0;							
	buf->last_pos = i;
											/* Waits for a slot to be free to fill it */
	while(true){
		sem_wait(&mutex);
		printf("stopped waiting\n");

	}



	close_file(file);
}
