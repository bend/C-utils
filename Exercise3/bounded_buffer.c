#include "bounded_buffer.h"

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
