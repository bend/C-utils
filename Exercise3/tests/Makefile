CC=gcc
CFLAGS=-W -Wall -Werror -ansi -pedantic
EXEC = test_file

all: $(EXEC)
$(EXEC): file_reader.o test_file_reader.o
		$(CC) -o $(EXEC) file_reader.o test_file_reader.o
file_reader.o: ../file_reader.c
		$(CC) -o file_reader.o -c ../file_reader.c $(CFLAGS)
file_test.o: file_test.c file_reader.h
		$(CC) -o file_reader.o -c test_file_reader.c $(CFLAGS)

.PHONY: clean mrproper
				            
clean:
		@rm *.o
mrproper: clean
		@rm $(EXEC)

