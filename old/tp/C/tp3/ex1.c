#include <stdio.h>
#include <stdlib.h>
#define NB_LIGNE 12
#define NB_COL 20
#define N 26
#define B ' '
 

 
void AfficheImage(unsigned char im[NB_LIGNE][NB_COL])

{
int i,j;

for(i=0;i<NB_LIGNE;i++)
  {
    for(j=0;j<NB_COL;j++)
      {
        
        printf("%c",im[i][j]);
        
      }
      printf("\n");
  }

}

void AfficheImageDansCadre(unsigned char im[NB_LIGNE][NB_COL])

{
int i,j;
printf("+");

for (i=0;i<NB_COL;i++)
  {
  printf("-");
  }
  printf("+\n");

for(i=0;i<NB_LIGNE;i++)
  {
  printf("|");

    for(j=0;j<NB_COL;j++)
      {
        
        printf("%c",im[i][j]);
        
      }
      printf("|\n");
  }
  printf("+");
for (i=0;i<NB_COL;i++)
  {
  printf("-");
  }
  printf("+\n");
}



int main ()

{

  unsigned char image_damier[NB_LIGNE][NB_COL] = {{B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},                       {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B },
  {B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},
  {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B},      
  {B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},
  {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B},
  {B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},
  {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B},
  {B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},
  {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B},
  {B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N},
  {N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B,N,B}};
  
  AfficheImageDansCadre(image_damier);

  return EXIT_SUCCESS;
}


  
