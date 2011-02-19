#include "file_reader.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FILE* open_file(const char* path){
	FILE* f;
		if((f=fopen(path, "r"))==NULL){
			perror("cannot open file");
			exit(-1);
		}	
		return fopen(path, "r");
}

int close_file(FILE* file){
	return fclose(file);
}

char* get_next(FILE* f){
	char temp[50];
	int length;
	char* final_string;
		fgets(temp,50,f);
		if(temp==NULL || temp[0]==EOF)
			return NULL;
		length = strlen(temp);
		if(length<2)
			return NULL;
		final_string = malloc(sizeof(char)*length);
		if(final_string == NULL){
			perror("malloc failed");
			exit(-1);
		}	
		strncat(final_string, temp,length-1);
		return final_string;
}
/*
int main(){
	FILE *f;
	int i;
	char* t;
	f= open_file("/Users/benoitdaccache/Documents/Programation/C-System/Exercise3/test.txt");
	i=0;
	t=get_next(f);
	while(t!=NULL){
		printf("|%s|\n",t);
		i++;
		t = getNextWord(f);
	}
	close_file(f);
	return EXIT_SUCCESS;
}
*/
