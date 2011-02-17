#include <stdio.h>

/* Returns the next line in the file if it exist */
/* Otherwise returns NULL 						 */
char* get_next(FILE* f);

/* Opens the file in READONLY mode 		*/
/* Returns a FILE pointer if succeeded  */
/* Returns NULL otherwise				*/
FILE* open_file(const char* path);

int close_file(FILE* file);
