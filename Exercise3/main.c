#include <string.h>
#include <stdio.h>

#include "zip_crack.h"
#include "cracker.h"
#include "file_reader.h"

void
usage (void)
{
    printf("zipcrack ZIP_FILE [PASSWORD1 [PASSWORD2 ...]]\n");
}

int 
main (int argc, char const * argv[])
{
  int i;
	FILE *f;
	

    struct zip_archive * archive;


	f= open_file("/Users/benoitdaccache/Documents/Programation/C-System/Exercise3/test.txt");
	printf("%s\n",get_next(f));


    if (argc < 2) {
        usage();
        return 1;
    }

    if ( (archive = zip_load_archive(argv[1])) == NULL) {
        printf("Unable to open archive %s\n", argv[1]);
        return 2;
    }

    for (i = 2; i < argc; i++) {
        if(zip_test_password(archive, argv[i]) == 0) {
            printf("Password is: %s\n", argv[i]);
            goto finish;
        }
    }

    printf("Password not found\n");

finish:   
    zip_close_archive(archive);
    return 0;
}
