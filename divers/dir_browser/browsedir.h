/*
 * =====================================================================================
 *
 *       Filename:  browsedir.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03.05.2011 12:37:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */


#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX_PATH	4096	/* Maximum length of the path */
#define DIR_SYM		"+"		/* The directory symbol */
#define FILE_SYM	"|"		/* The File symbol */
#define TAB			"  "	/* The default tabultation */


void browse_dir(char* path, unsigned int rec_level, long *nb_files, long *nb_folders);

void print_dir(struct dirent* ent, unsigned int rec_level);

void print_file(struct dirent* ent, unsigned int rec_level);

void print_total(long nb_files, long nb_folders);

char* build_path(char* path, char* filename);
