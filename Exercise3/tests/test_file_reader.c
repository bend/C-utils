#include "../file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_file_reader(){
	FILE* f;
		f=open_file("tests.txt");
		assert(strcmp(get_next(f),"line1")==0);
		assert(strcmp(get_next(f),"line2")==0);
		assert(strcmp(get_next(f),"line 3")==0);
		assert(strcmp(get_next(f),"line4 line5")==0);
		assert(strcmp(get_next(f),"1 2 3 4 5 6 7 8 9 10 11 12 13")==0);
}


int main(){

	test_file_reader();
	printf("All tests succeeded\n");
	return EXIT_SUCCESS;
}

