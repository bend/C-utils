#include "cracker.h"
#include <string.h>



void*
crack_password(void* arg){
  	params* p;
	buffer* buf;
	char* pass;
	struct zip_archive * archive;
		p =(params*)arg;
		buf = p->buf;
		if ((archive = zip_load_archive(p->zipfile)) == NULL) {
			printf("Unable to open archive %s\n", p->zipfile);
			exit(-1);
		 }
		sleep(2);
		do{	
		  	sem_wait(p->full);
			pass = bounded_buffer_get(buf);
			if(pass != NULL){
				printf("test pass %s\n",pass);
				if(zip_test_password(archive, pass) == 0) {
					printf("Password is: %s\n", pass);
					free(pass);
					bounded_buffer_free(buf);
					free(p);
					exit(0);
				}
			}else printf("looping\n");
			sem_post(p->empty);
		}while(1);

		pthread_exit(NULL);

}


void*
fill_buffer(void* arg){
	params* p;
	buffer* buf;
	char* temp;
	FILE* file;
		p=(params*)arg;
		buf=p->buf;
		file = open_file(p->dictionary);    /*            		  Open file        */
		do{
		  	sem_wait(p->empty);
			if(buf->nb_elem < buf->size){
				temp = get_next(file);
				printf("producer  add %s\n",temp);
				bounded_buffer_put(buf, temp);
			}
			sem_post(p->full);
		}while(temp!=NULL);


	pthread_exit(NULL);
}


void 
create_threads(unsigned int nb_threads, buffer* buf, char* file_to_crack, char* dictionary_file){
	pthread_t *threads;										/*Array of threads*/
	int rc;
	int i;
	int pthread_join_res;
	params *crack_params;
	sem_t *full;
	sem_t *empty;
	pthread_mutex_t *mutex;
	empty = sem_open("semshm",O_CREAT , 0600, buf->size);          
	full = sem_open("semshm2",O_CREAT , 0600, 0);
		
		threads = malloc(sizeof(pthread_t)*nb_threads+1);			/* nb_threads+1 for storing the bounded_buffer thread*/
		if(threads == NULL){
			perror("malloc failed");
			bounded_buffer_free(buf);
			exit(-1);
		}
		
		crack_params = malloc(sizeof(params*));
		if(crack_params == NULL){
			perror("malloc failed");
			free(threads);
			bounded_buffer_free(buf);
			exit(-1);
		}
		crack_params->zipfile= file_to_crack;
		crack_params->dictionary= dictionary_file;
		crack_params->empty = empty;
		crack_params->full = full;
		crack_params->mutex = mutex;
		crack_params->buf = buf;
		for(i=0; i<nb_threads; i++){						/* create crack threads */
			rc = pthread_create(&threads[i],NULL,crack_password,(void*)crack_params);   /*Creating thread*/
			if (rc){
				printf("ERROR; return code from pthread_create() is %d\n", rc);
			    free(threads);
				bounded_buffer_free(buf);
				free(crack_params);
			    exit(-1);
			}
		}
		
		rc =pthread_create(&threads[nb_threads],NULL,fill_buffer,(void*)crack_params);
		if(rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
            free(threads);
			bounded_buffer_free(buf);
			free(crack_params);
			exit(-1);
		}
		for(i=0; i<nb_threads+1; i++)
			pthread_join_res = pthread_join(threads[i], NULL);
		
		bounded_buffer_free(buf);
		free(crack_params);
		free(threads);
}


void create_process(unsigned int nb_process, buffer* buff, char* file_to_crack, char* dictionary_file){
	params* shared;
	pid_t pid;
	int i;
	sem_t *empty;
	sem_t *full;
	empty = sem_open("semshm",O_CREAT , 0600, buff->size);
	full = sem_open("semshm2",O_CREAT , 0600, 0 );

	shared = create_mem_segment(1234);
	shared->buf = buff;
	shared->dictionary=dictionary_file;
	shared->zipfile = file_to_crack;
	shared->full = full;
	/*    shared_values = (int *)mmap(NULL, shared_seg_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0); */
	for(i=0; i<nb_process+1; i++){
		pid=fork();
		if(i==(nb_process)){
			if(pid==0){
			  	params* temp;
			  	printf("creating fill proc\n");
			  	temp= get_mem_segment(1234);
				fill_buffer(temp);
			}else if(pid<0){
				perror("fork error");
				exit(-1);
			}
		}else{	
			if(pid==0){
			  	params* temp;
			  	printf("creating crack  proc\n");
				temp = get_mem_segment(1234);
				crack_password(temp);
			}else if(pid<0){
				perror("fork error");
				exit(-1);
			}
		}	  
	}
	wait(0);
}


void start_cracking(char tp, unsigned int nb_pt, char* file_to_crack, char* dictionary_file){
	buffer* buf;
		buf=bounded_buffer_new(10);
		if(tp=='p')
			create_process(nb_pt, buf,file_to_crack, dictionary_file);
		else
			create_threads(nb_pt,buf, file_to_crack, dictionary_file);
}


params* create_mem_segment(key_t key ){
    int shmid;  
  	params *shm,*r;
  
  
  	if ((shmid = shmget(key, sizeof(params*), IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(-1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (params *) -1) {
		perror("shmat");
		exit(-1);
	}
	r=shm;
	return r;
}


params*  get_mem_segment(key_t key){
	int shmid;
	params* shm,*r;
	
  	if ((shmid = shmget(key,sizeof(params*) , 0666)) < 0) {
    	perror("shmget");
		exit(1);
	}

    if ((shm = shmat(shmid, NULL, 0)) == (params *) -1) {
		perror("shmat");
		exit(1);
	}
	
	r=shm;
	return r;

}


