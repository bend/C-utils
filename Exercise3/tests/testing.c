#include "../file_reader.h"
#include "../bounded_buffer.h"

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

void test_buffer(){
	buffer *buf;
		buf = bounded_buffer_new(5);
		assert(bounded_buffer_put(buf,"test1") == 0);
		assert(bounded_buffer_put(buf,"test2") == 0);
		assert(bounded_buffer_put(buf,"test3") == 0);
		assert(bounded_buffer_put(buf,"test4") == 0);
		assert(bounded_buffer_put(buf,"test5") == 0);
		assert(bounded_buffer_put(buf,"test6") == -1);
		
		assert(strcmp(bounded_buffer_get(buf),"test1")==0);
		
		assert(bounded_buffer_put(buf,"test6") == 0);
		assert(bounded_buffer_put(buf,"test8") == -1);
		
		assert(strcmp(bounded_buffer_get(buf),"test2")==0);
		assert(strcmp(bounded_buffer_get(buf),"test3")==0);
		assert(strcmp(bounded_buffer_get(buf),"test4")==0);
		assert(strcmp(bounded_buffer_get(buf),"test5")==0);
		assert(strcmp(bounded_buffer_get(buf),"test6")==0);
		assert(bounded_buffer_get(buf) == NULL);


}


int main(){

	test_file_reader();
	test_buffer();
	printf("All tests succeeded\n");
	return EXIT_SUCCESS;
}

