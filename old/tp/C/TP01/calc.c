#include <stdio.h>
#include <stdlib.h>

int main()


{
char o;
int a,b;
  printf("---------------------------\n");
  printf("programme calculette entier\n");
  printf("---------------------------\n");
  
      printf("operateur(+, -, *): ");
      scanf("%c",&o);
      printf("%c",o);
 
 
  printf("premier entier: ");
  scanf("%d",&a);  
  printf("deuxieme entier: ");
  scanf("%d",&b);
  
  if (o=='+') 
    printf("%d %c %d = %d\n",a,o,b,a+b);
  else if (o=='-')    
   printf("%d %c %d = %d\n",a,o,b,a-b);
  else if (o=='*')    
    printf("%d %c %d = %d\n",a,o,b,a*b);
    else
    printf("caractere incorect \n ");
    return EXIT_SUCCESS;
}