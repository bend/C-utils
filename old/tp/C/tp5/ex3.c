#include <stdio.h>
#include <stdlib.h>

void permut(int* adr_a,int* adr_b)
{
	int c;
	c=*adr_a;
	*adr_a=*adr_b;
	*adr_b=c;
}





int main()
{
	int a,b;
	printf("entrez a et b\n");
	scanf("%d\n%d",&a,&b);
	permut(&a,&b);
	
	
	printf("a: %d b:%d\n",a,b);
return EXIT_SUCCESS;
}
