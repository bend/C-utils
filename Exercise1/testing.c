#include "str_buf.h"

#include <assert.h>
#include <stdio.h>

void
test_str_buf_alloc(){
    str_buf *b1;
    str_buf *b2;
	b1 = str_buf_alloc(10);
	assert(str_buf_len(b1) == 0);
	b2 = str_buf_alloc_str("abc");
	assert(str_buf_len(b2)==3);
	str_buf_free(b1);
	str_buf_free(b2);
}

void
test_str_buf_free(){
    str_buf *b1;
    str_buf *b2;
    b1 = str_buf_alloc(100);
    b2 = str_buf_alloc_str("abcdef");
    str_buf_free(b1);
    str_buf_free(b2);
}

void
test_str_buf_head(){
    str_buf *b1;
	b1 = str_buf_alloc_str("abc");
	assert(strcmp(str_buf_head(b1) , "abc")==0);
	assert(str_buf_len(b1)==3);
	str_buf_free(b1);
}

void
test_str_buf_alloc_substr(){
    str_buf *b1;
    str_buf *b2;
	b1 = str_buf_alloc_substr("abcdef",4);
	b2 = str_buf_alloc_substr("abcdef",4);
	assert(strcmp(str_buf_head(b1) , "abcd")==0);
	assert(str_buf_equals(b1,b2));
	assert(str_buf_len(b1)==4);
	str_buf_free(b1);
	str_buf_free(b2);
}

void
test_str_buf_len(){
    str_buf *b1, *b2;
	b1 = str_buf_alloc(10);
	b2 = str_buf_alloc_str("abc");
	assert(str_buf_len(b1)==0);
	assert(str_buf_len(b2)==3);
        str_buf_free(b1);
        str_buf_free(b2);
}

void 
test_str_buf_concat(){
    str_buf * b1;
    str_buf * b2;
    str_buf * b3;
    str_buf * b4;
    str_buf * b5;
    str_buf * b6;
    str_buf * b7;
		
	b1 = str_buf_alloc(10);
	b2 = str_buf_alloc_str("abc");
	b3 = str_buf_alloc_str("wxyz");

	b4 = str_buf_concat(b1, b2);

	    
	assert(str_buf_len(b4) == 3);
	assert(str_buf_equals(b4, b2));
	
	b5 = str_buf_concat(b2, b1);
	    
	assert(str_buf_equals(b5, b2));
	assert(str_buf_len(b5) == 3);
	
	b6 = str_buf_concat(b4, b3);
	b7 = str_buf_alloc_str("abcwxyz");
	assert(str_buf_equals(b6, b7));
	
	str_buf_free(b1);
	str_buf_free(b2);
	str_buf_free(b3);
	str_buf_free(b4);
	str_buf_free(b5);
	str_buf_free(b6);
	str_buf_free(b7);	
}

void test_str_buf_put_str(){
    str_buf *b1;
	b1 = str_buf_alloc(10);
	assert(str_buf_put_str(b1,"abcdef"));
	assert(strcmp(str_buf_head(b1),"abcdef")==0);
        str_buf_free(b1);
}

void
test_str_buf_put_buf(){
    str_buf *b1;
    str_buf *b2;
    str_buf *b3;
    str_buf *b4;
	b1 = str_buf_alloc(10);
	b2 = str_buf_alloc_str("abcdef");
	assert(str_buf_put_buf(b1,b2));
	assert(strcmp(str_buf_head(b1),"abcdef")==0);
	b3 = str_buf_alloc(10);
	b4 = str_buf_alloc_str("efg");
	assert(str_buf_put_str(b3,"abcd"));
	assert(str_buf_put_buf(b3,b4));
	assert(strcmp(str_buf_head(b3),"abcdefg")==0);
        str_buf_free(b1);
        str_buf_free(b2);
        str_buf_free(b3);
        str_buf_free(b4);
}

void test_str_buf_put_substr(){
    str_buf *b1;
	b1 = str_buf_alloc(10);
	assert(str_buf_put_substr(b1,"abcdef",2));
	assert(strcmp(str_buf_head(b1),"ab")==0);
        str_buf_free(b1);
}

int main (int argc, char const *argv[]){
	test_str_buf_alloc();
	test_str_buf_free();
	test_str_buf_head();
	test_str_buf_alloc_substr();
	test_str_buf_len();
	test_str_buf_concat();
	test_str_buf_put_str();
	test_str_buf_put_buf();
	test_str_buf_put_substr();

	printf("Tests have succeeded\n");
    return 0;
}