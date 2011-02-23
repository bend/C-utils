CC=gcc
CFLAGS=-W -Wall -Werror -ansi -pedantic -g
EXEC = tests

all: $(EXEC)

$(EXEC): testing.o file_reader.o bounded_buffer.o my_sem.o
	$(CC) -o tests testing.o file_reader.o bounded_buffer.o my_sem.o
file_reader.o: ../file_reader.c
	$(CC) -o file_reader.o -c ../file_reader.c $(CFLAGS)
bounded_buffer.o: ../bounded_buffer.c
	$(CC) -o bounded_buffer.o -c ../bounded_buffer.c $(CFLAGS)
my_sem.o: ../my_sem.c
	$(CC) -o my_sem.o -c ../my_sem.c $(CFLAGS)
testing.o: testing.c ../file_reader.h ../bounded_buffer.h ../my_sem.h
	$(CC) -o testing.o -c testing.c $(CFLAGS)

.PHONY: clean mrproper
                            
clean:
	@rm *.o
mrproper: clean
	@rm $(EXEC)

