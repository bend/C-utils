#include "cracker.h"


void startBoundedBuffer(char** buffer){
	for(i=0; i<BB_SIZE; i++){
		buffer[i] = readNext(f);
	}

	
}
