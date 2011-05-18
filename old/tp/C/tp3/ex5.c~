#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NB_LIGNE 20
#define NB_COL 30
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

void ImageAleatoire(unsigned char im[NB_LIGNE][NB_COL])
{
   srand (time(NULL));
 int i,j;
 
 for(i=0;i<NB_LIGNE;i++)  
 {
  for (j=0;j<NB_COL;j++)
  {
    if(rand()%2==0) 
      {
        im[i][j]=N;
       }
    else 
      im[i][j]=B;
   }   
   }
 }  
   

void InverserImage(unsigned char im[NB_LIGNE][NB_COL])
{
int i,j;
for(i=0;i<NB_LIGNE;i++)  
 {
  for (j=0;j<NB_COL;j++)
  {
    if(im[i][j]==N)
       im[i][j]=B;
    else if (im[i][j]==B)
    im[i][j]=N;
  }
}




}

void RemplitImage(unsigned char im[NB_LIGNE][NB_COL],unsigned char couleur)
{
  int i,j;
for(i=0;i<NB_LIGNE;i++)  
 {
  for (j=0;j<NB_COL;j++)
  {
    
       im[i][j]=couleur;
      
}
  




}

}

void Bande(unsigned char im[NB_LIGNE][NB_COL])
{
  for(i=0;i<NB_LIGNE;i++)  
   {
    for (j=1;j<NB_COL;j++)
      {
        int n
     






}
int main ()

{
  
  unsigned char image[NB_LIGNE][NB_COL];
  
  RemplitImage(image,B);
  AfficheImageDansCadre(image);
  return EXIT_SUCCESS;
}


  
