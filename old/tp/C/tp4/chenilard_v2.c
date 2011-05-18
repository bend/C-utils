#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Temporisation(long int millisecondes)
{
  clock_t start = clock();
  clock_t stop =  start+(millisecondes*CLOCKS_PER_SEC/1000);
  while (clock()<stop);
}

int main(int argc, char* argv[])
{
  
  int i;
  int n;
  char E='.';
  char A='@';
  int nb=20;
  int tps=400;
  int erreur=0;
if (argc>=2);
  {for(i=1;i<argc;i=i+2)
    {
    if (argv[i][0]=='-')
        {
          if (argv[i][1]=='a')  
            A=argv[i+1][0];
      
          else if (argv[i][1]=='e')
      
            E=argv[i+1][0];
      
          else if (argv[i][1]=='n')
      
            nb=atoi(argv[i+1]);
    
          else if (argv[i][1]=='t')
    
            tps=atoi(argv[i+1]);
	else erreur=i;
      } 
    } 
  }
  char V[nb];

while (erreur==0)
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
        printf("\a"); 
     }  
  
}
if(erreur!=0)
	{
		printf("%s : L'operande est invalide\n",argv[erreur]);
}


  return EXIT_SUCCESS;
}