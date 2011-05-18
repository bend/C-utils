#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define E '.'
#define A '@'
#define nb 20
#define tps 300



void Temporisation(long int millisecondes)
{
  clock_t start = clock();
  clock_t stop =  start+(millisecondes*CLOCKS_PER_SEC/1000);
  while (clock()<stop);
}

int main()
{
  char V[nb]={E};
  int i;
  int n;





while (1)
{
  for(i=0;i<nb;i++)
    {
      for (n=0;n<nb;n++)
        {
          
      
          if (n==i)
            {
              V[i]=A;
             }
             else 
               V[i]=E;
          putchar(V[i]); 
      }
        Temporisation(tps);
        fflush(stdout);
        printf("\r");
        putchar('\a');
          
     }  
  
}
  return EXIT_SUCCESS;
}
