#include "file_reader.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

FILE* 
open_file(const char* path){
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

void
get_next(FILE* f, char* pass){
	int length;
		fgets(pass,50,f);
		length = strlen(pass);
		pass[length-1] = '\0';
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
