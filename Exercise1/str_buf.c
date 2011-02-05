#include "str_buf.h"

struct str_buf{
    size_t size;
    int length;
    char* buffer;
};


str_buf * 
str_buf_alloc(size_t size){
    str_buf *myBuffer;
	myBuffer = malloc(sizeof(struct str_buf));	
	myBuffer->buffer = malloc(size);
	myBuffer->length=0;
	myBuffer->size = size;
	if(myBuffer->buffer == NULL)		/* if malloc faild, return false */
	    return NULL;
	return myBuffer;
}

str_buf * 
str_buf_alloc_str(const char * str){
    str_buf *myBuffer;
    size_t len;
    int i;
	len= strlen(str);
	myBuffer = malloc(sizeof(struct str_buf));
	myBuffer->buffer = malloc(len);
	if(myBuffer->buffer == NULL)		/* if malloc faild, return false */
	    return NULL;
	for(i=0; i<len; i++)
	    myBuffer->buffer[i] = str[i];	/* put the string into the buffer */
	myBuffer->length = len;			/* setting length  		  */
	myBuffer->size = len;			/* setting size of buffer (equals length) */
	return myBuffer;
}

str_buf * 
str_buf_alloc_substr(const char * str, size_t str_len){
    str_buf *myBuffer;
    int i;
	myBuffer = malloc(sizeof(struct str_buf));
	myBuffer->buffer = malloc(str_len);
	if(myBuffer->buffer == NULL)		/* if malloc faild, return false */
	    return NULL;
	for(i=0; i<str_len; i++)
	    myBuffer->buffer[i] = str[i];	/* put the string into the buffer */
	myBuffer->length = str_len;		/* setting length  		  */
	myBuffer->size = str_len;		/* setting size of buffer (equals length )*/
	return myBuffer;
}

void 
str_buf_free(str_buf * buf){
    free(buf->buffer);
    free(buf);
}

const char *
str_buf_head(str_buf * buf){
    return buf->buffer;
}

size_t 
str_buf_len(str_buf * buf){
    return buf->length;
}

size_t 
str_buf_size(str_buf * buf){
    return buf->size;
}

str_buf * 
str_buf_concat(str_buf * buf1, str_buf * buf2){
    int len1, len2;
    str_buf *myBuffer;
    const char* str1;
    const char* str2;
    int i;
    int j;
	len1 = str_buf_len(buf1);
	len2 = str_buf_len(buf2);
	str1 = str_buf_head(buf1);
	str2 = str_buf_head(buf2);
	myBuffer = malloc(sizeof(*myBuffer));
	myBuffer->buffer = malloc(len1+len2);
	if(myBuffer->buffer == NULL)		/* if malloc faild, return false */
	    return NULL;
	for(i=0; i<len1; i++)			/* putting the string of buf1 in the newBuffer*/
	    myBuffer->buffer[i] = str1[i];
	for(j=0;j<len1+len2;i++,j++)		/* appending the string contained in buf2 in the newBuffer */
	    myBuffer->buffer[i] = str2[j];
	myBuffer->length = len1+len2;		/* setting length  		  */		
	myBuffer->size = len1+len2;		/* setting size of buffer (equals length )*/
	return myBuffer;
}

bool
str_buf_equals(str_buf * buf1, str_buf * buf2){
    if(buf1->length != buf2->length)		/* if the size of the 2 strings differs, return false */ 
	return false;
    int i;
	for(i=0; i<str_buf_len(buf1);i++)
	    if(buf1->buffer[i]!= buf2->buffer[i])/* if the character is not the same return false 	*/
		return false;
    return true;
}

bool 
str_buf_put_buf(str_buf * buf1, str_buf * buf2){
    int i;
    int j;
	if(str_buf_size(buf1)< str_buf_len(buf1)+str_buf_len(buf2))		/* check if the buf1 size is big enough append buf2 to buf1*/
	    return false;
	for (i=str_buf_len(buf1),j=0; j<str_buf_len(buf2); i++,j++){
	    buf1->buffer[i] = buf2->buffer[j];					/* append buf2 to buf1 */
	    buf1->length++;
	}
	return true;
}

bool 
str_buf_put_str(str_buf * buf, const char * str){
    int i;
    int j;
	if(str_buf_size(buf)< str_buf_len(buf)+strlen(str))		/* check if the buf size is big enough append str to buf1*/
	    return false;
	for (i=str_buf_len(buf),j=0; j<strlen(str); i++,j++){
	    buf->buffer[i] = str[j];					/* append str to buf */
	    buf->length++;
	}
	return true;
}

bool
str_buf_put_substr(str_buf * buf, const char * str, size_t str_len){
    int i;
    int j;
	if(str_buf_size(buf)< str_buf_len(buf)+str_len)			/* check if the buf size is big enough append the substring of str to buf1*/
	    return false;
	for (i=str_buf_len(buf),j=0; j<str_len; i++,j++){
	    buf->buffer[i] = str[j];					/* append substring of str to buf */
	    buf->length++;
	}
	return true;

}
