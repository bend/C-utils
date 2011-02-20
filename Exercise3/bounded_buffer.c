#include "bounded_buffer.h"
#include "file_reader.h"

buffer*  
bounded_buffer_new(unsigned int size){
	buffer *buf;

	buf = malloc(sizeof(buffer));
	if(buf == NULL){
		perror("Error in malloc");
		exit(-1);
	}
	buf->array = malloc(sizeof(char*)*size);
	if(buf->array == NULL){
		free(buf);
		perror("malloc error");
		exit(-1);
	}
	buf->last_pos = 0;
	buf->first_pos =0;
	buf->nb_elem = 0;
	buf->size = size;
	return buf;
}


void
bounded_buffer_fill(buffer *buf){
	int i;
	FILE *file;
	char* path= "tests/tests.txt";
	char* t;

	i=0;
	file = open_file(path);					/* Open file 		*/
	t=get_next(file);
	while(t!=NULL && i<(int)buf->size){				/* fill buffer */
		buf->array[i++] = t;
		t=get_next(file);
	}
	buf->first_pos = 0;							
	buf->last_pos = i;
											/* Waits for a slot to be free to fill it */
	close_file(file);
}


char* 
bounded_buffer_get(buffer *buf){
	char* str;
		if(buf->nb_elem == 0)
			return NULL;
		str = buf->array[buf->first_pos];
		buf->first_pos = (buf->first_pos + 1) % buf->size;
		buf->nb_elem--;
		return str;
}


int
bounded_buffer_put(buffer *buf, char* str){
	if(buf->nb_elem == buf->size)
		return BUFFER_FULL;
	buf->array[buf->last_pos % buf->size] = str;
	buf->last_pos = (buf->last_pos + 1) % buf->size;
	buf->nb_elem++;
	return BUFFER_SUCCESS;
}


void 
bounded_buffer_free(buffer *buf){
	unsigned int i;
		for(i=buf->first_pos; i<buf->last_pos; i++)
			free(buf->array[i]);
		free(buf->array);
		free(buf);
}
