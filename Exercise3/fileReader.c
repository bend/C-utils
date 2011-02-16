#include "fileReader.h"


FILE* openFile(const char* path){
	return fopen(path, "r");
}

int closeFile(FILE* file){
	return fclose(file);
}

char* getNextWord(FILE* f){


	return NULL;
}
