#include <stdio.h>
#include <stdlib.h>


void carre(int* adr_x)
{
	*adr_x=(*adr_x)*(*adr_x);
	
}


int main()
{	
	int x;
	printf("entrez la valeur ");
	scanf("%d",&x);
	carre(&x);
	printf("%d\n",x);
	return EXIT_SUCCESS;
}

