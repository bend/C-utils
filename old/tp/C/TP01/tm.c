#include <stdio.h>
#include <stdlib.h>

int main()


{
int a,i;
  printf ("Vous voulez la table de multiplication de combien :\n");
  scanf ("%d",&a);
  
  for (i=0 ; i<=10;i++)
    
      printf("%d X %d = %d \n",a,i,a*i);
return EXIT_SUCCESS;     
}
