#include "../file_reader.h"
#include "../bounded_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_file_reader(){
	FILE* f;
	char pass[50];
		f=open_file("tests.txt");
		get_next(f,pass);
		assert(strcmp(pass,"line1")==0);
		get_next(f,pass);
		assert(strcmp(pass,"line2")==0);
}

void test_buffer(){
	buffer *buf;
	char pass[50];
		buf = bounded_buffer_new();
		assert(bounded_buffer_put(buf,"test1") == 0);
		assert(bounded_buffer_put(buf,"test2") == 0);
		assert(bounded_buffer_put(buf,"test3") == 0);
		assert(bounded_buffer_put(buf,"test4") == 0);
		assert(bounded_buffer_put(buf,"test5") == 0);
		
		bounded_buffer_get(buf, pass);
		assert(strcmp(pass,"test1")==0);
		


}


int main(){

	test_file_reader();
	test_buffer();
	printf("All tests succeeded\n");
	return EXIT_SUCCESS;
}

