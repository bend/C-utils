#include <stdio.h>
#include <stdlib.h>


char* stringdup(char* s)
{
	int i=0;
	int j=0;
	while(s[i]!='\0')
	{
		i=i+1;
	}
	char *tab= (char*)malloc((i+1)*sizeof(char));
	while(j<i) 
	{	
		tab[j]=s[j];
		j++;
	}
	
	return tab;	
		
}



int main()
{	
	char *z;
	char s[20];
	scanf("%s",s);
	z=stringdup(s);
	printf("%s\n",z);
return EXIT_SUCCESS;
}
