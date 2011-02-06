all: str_buf.o

tests: str_buf.o testing.o
	gcc -o test str_buf.o testing.o -Wall -Werror
	./test
str_buf.o: str_buf.c
	gcc -o str_buf.o -c str_buf.c -Wall -Werror
testing.o: testing.c str_buf.h
	gcc -o testing.o  -c testing.c -Wall -Werror
            
clean:
	rm *.o
