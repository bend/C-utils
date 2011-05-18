#include <stdio.h>
#include <stdlib.h>
		
void affichecar(int n, char c)
{	
int i;
for (i=0; i<n;i++)	
	putchar(c);
}

int main (int argc,char *argv[])
{ 

int i;


char space=' ' ;
int hauteur;
hauteur=atoi(argv[1]);

char car=*argv[2];
int base= ((2*hauteur)-1);
int nbspace = ((base-1)/2);
int nbcar = (base-(2*nbspace));
for(i=0;i<hauteur;i++)
{


	base=base-2;
	affichecar(nbspace,space);
	affichecar(nbcar,car);
	base=base-2;
	nbspace=nbspace-1;
	nbcar=nbcar+2;
	printf("\n");
}	


return EXIT_SUCCESS;
}

