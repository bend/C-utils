#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define delta(a,b,c) ((b)*(b) - 4*(a)*(c))
#define x1(a,b,d) (((-b)-(sqrt(d)))/(2*a))
#define x2(a,b,d) (((-b)+(sqrt(d)))/(2*a))
#define debug 1
int main (int argc, char * argv[])
{
	



	if (argc!=4)
	{
		printf("mauvais nombre de parametres\n");
		printf("usage : macro_racine <a> <b> <c>\n");
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = atoi(argv[3]);


	int d = delta(a,b,c);
#if debug
	printf("Delta %d\n",d);
	printf("argument 0 %s\nargument 1 %s\nargument 2 %s\nargument 3 %s\n",argv[0],argv[1],argv[2],argv[3]);
#endif
	if(d<0)
		printf("Delta negatif pas de racines\n");
	else if(d==0)
	{
		int res = x1(a,b,d);
		printf ("r = %d\n",res);
	}
	
	else if (d>0)
	{
		int res1= x1(a,b,d);
		int res2= x2(a,b,d);
		printf("r1 = %d\nr2 = %d\n",res1,res2);
	}

		

return EXIT_SUCCESS;
}