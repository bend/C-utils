#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i=0;
	int n;
	printf("entrez le nombre d'elements\n");
	scanf("%d",&n);
	int *tab = (int*)malloc((n+1)*sizeof(int));
	while(i<n) 
	{
		printf("element %d\n",i);
		scanf("%d",&tab[i]);
		i++;
	}
	i=0;
	int j,c;
	while( i<n)
	{	
		j = n-1;
		while (j>i)
		{
			if (tab[j-1]>tab[j])
			{	
				c=tab[j-1];
				tab[j-1]=tab[j];
				tab[j]=c;
			}
			j--;
		
		}
		i++;
	}
	
	i=0;
	while (i<n)
	{
		printf("%d\n",tab[i]);
		i++;
	} 			
	return EXIT_SUCCESS;

}	