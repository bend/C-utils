#ifndef __CRACKER_H__
#define __CRACKER_H__
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "bounded_buffer.h"
#include "file_reader.h"
#include "my_sem.h"
#define SHMSZ     27

struct params{
	buffer* buf;
	char* dictionary;
	char* zipfile;
	sem_t* empty;
	sem_t* full;
	pthread_mutex_t *mutex;
};

typedef struct params params;
/*
* Fills the buffer with words from dictionary
* @param : arg the struct containing the struct buffer and the filename of the dict.
*/
void* fill_buffer(void* arg);


/*
* Starts cracking the password with words from the bounded buffer 
* @param: arg : a struct contining the buffer and the filename to crack
*/
void* crack_password(void* arg);

/*
* Create nb_threads threads and starts the crack routine
* @params nb_threads: the number of threads to be created
* @params p : params containing the buffer and the filename of the file to crakc(see params declaration on top of file)
*/
void create_threads(unsigned int nb_threads, buffer *buf, char* file_to_crack, char* dictionary_file);


/*          
* Create nb_process process and starts the crack routine
* @params nb_process: the number of process to be created
* @params p : params containing the buffer and the filename of the file to crack (see params declaration on top of file)
*/
void create_process(unsigned int nb_process, buffer* buff, char* file_to_crack, char* dictionary_file);

/*
* Starts the crack by creating process or threads (tp=='t' for threads ana 'p' for process)
* @param tp: a character that determine if we use threads (t) or process(p). if other value is entered, threads will be used
* @param nb_pt: the number of threads or process to use, tp must be >0
* @param file_to_crack: the path to the zip file to crack
* @param dictionary_file: the path to the dictionary to use
*/
void start_cracking(char tp, unsigned int nb_pt, char* file_to_crack, char* dictionary_file);

params* create_mem_segment(key_t key );

params*  get_mem_segment(key_t key );
#endif





