#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int n;
  printf("entrez un entier\n");
  scanf("%d" , &n);
  if (n % 2 == 0) 
    printf(" Avec le modulo, %d est pair\n",n);
  else 
    printf(" Avec le modulo, %d est impair\n",n);

int res= 0x00000001;

if (((res)&(n))==1)
  printf("avec le masque binaire %d est impair\n",n);
else
  printf("avec le masque binaire %d est pair\n",n);




return EXIT_SUCCESS;
}
