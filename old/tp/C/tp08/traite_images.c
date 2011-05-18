#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEBUG 	0
#define OK	0
#define ERREUR	1

//---------------------------------------------------------------------------
struct image 
//---------------------------------------------------------------------------
{
	unsigned char* buffer ; // pointeur sur lespixels de l'image
	int largeur ; // largeur de l'image
	int hauteur ; // hauteur de l'image
} ;

//---------------------------------------------------------------------------
struct image LireImagePGM(char* nomFichier)
//---------------------------------------------------------------------------
// retourne la structure image remplie � partir du fichier nomFichier
// si probl�me, im.buffer = NULL
{
	FILE* f ;
	char s[256] ;
	char* c_res ;
	int i ;
	struct image im ; // la structure qui ser arenvoy�e

// part d�faut, pour les cas d'erreur
	im.buffer = NULL ;

// ouverture de l'image en lecture  
	f = fopen(nomFichier, "rb") ;
	if (!f)
	{
		printf("Erreur ouverture de fichier\n") ;
		return(im) ;
	}
	
// lecture des 4 premi�res lignes et r�cup�ration dimensions de l'image
	for (i=1; i<5; i++)
	{
		if (i == 3)
		{
			fscanf(f, "%d %d\n", &im.largeur, &im.hauteur) ;
#if DEBUG
			printf("Largeur=%d ; hauteur=%d\n", im.largeur, im.hauteur) ;
#endif
		}
		else
		{
			c_res = fgets(s, 255, f) ;
			if (c_res == NULL)
			{
				printf("Erreur lecture ligne %d\n", i) ;
				fclose(f) ;
				return(im) ;
			}
#if DEBUG
			printf("ligne %d : %s", i, s) ;
#endif
		}
	}
 
// allocation m�moire pour les pixels de l'image
	im.buffer = (unsigned char*) malloc(im.largeur*im.hauteur*sizeof(unsigned char)) ;
	if (im.buffer == NULL)
	{
		printf("Erreur d'allocation m�moire\n") ;
		fclose(f) ;
		return(im) ;
	}

// lecture des pixels de l'image
	fread(im.buffer, im.largeur,im.hauteur, f) ;
	
// fermeture fichier	
	fclose(f) ;
	return (im) ;
}

//---------------------------------------------------------------------------
int EcrireImagePGM(char* nomFichier, struct image im) 
//---------------------------------------------------------------------------
// cr�e (ou �crase) un fichier image avec les informations de la structure
{
	FILE* f ;

// ouverture de l'image � creer en �criture binaire	
	f = fopen(nomFichier, "wb") ;
	if (!f)
	{
		printf("Erreur ouverture de fichier en �criture\n") ;
		return ERREUR ;
	}
	
//  �criture de l'entete de l'image � creer
	fprintf(f, "P5\n") ;
	fprintf(f, "# CREATOR: Dept Info, IUT2 Grenoble\n") ;
	fprintf(f, "%d %d\n", im.largeur, im.hauteur) ;
	fprintf(f, "255\n") ;

	fwrite(im.buffer, im.largeur, im.hauteur, f) ;
	fclose(f) ;

	return OK ;
}	

//---------------------------------------------------------------------------
void SeuillerImage(struct image* im, unsigned char seuil)
//---------------------------------------------------------------------------
// transforme en noir et blanc les pixels de l'image pass�e en param�tre
// 0 <= seuil <= 255 pour un r�sultat avec plus ou moins de noir / blanc
{
	long int i ;

	for (i=0; i< im->largeur * im->hauteur; i++)
		*(im->buffer+i) = (*(im->buffer+i) < seuil) ? 0 : 255 ;
}

//---------------------------------------------------------------------------
void NegatifImage(struct image* im)
//---------------------------------------------------------------------------
// passe en n�gatif les pixels de l'image pass�e en param�tre
{
	long int i ;

	for (i=0; i< im->largeur * im->hauteur; i++)
		*(im->buffer+i) = 255 - *(im->buffer+i) ;
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
//---------------------------------------------------------------------------
{
	struct image im ; 

  char fileName[256];
  char commande;
  int k;
  int seuil;

// saisie du nom du fichier
  if (argc == 2)
    strcpy(fileName, argv[1]);
  else
  {
    printf("usage: traite_image <file> \n");
    return EXIT_FAILURE ;
  }

// lecture de l'image
	im = LireImagePGM(fileName) ; // on r�cup�re l'image lue
	if (im.buffer == NULL)
	{
		return EXIT_FAILURE ;
	}

// traitement
  k=1;
  while (k)
  {
    printf("Quel traitement souhaitez-vous appliquer? <N>egatif ; <S>euillage ; <Q>uitter\n");
    scanf("\n%c", &commande);
   
    switch(commande)
    {
      case 'n': case 'N':
              NegatifImage(&im) ; // on va modifier l'image. On passe donc l'adresse de la structure
              break;
      case 's': case 'S':
              printf("valeur du seuil?\n");
              scanf("%d", &seuil);
              SeuillerImage(&im, (unsigned char)seuil) ; // on va modifier l'image. On passe donc l'adresse de la structure
              break;
      case 'q': case 'Q':
              printf("nom du fichier � sauver?\n");
              scanf("%s", fileName);
              k = 0;
              break;
    }
		fflush(stdin) ;
  }

// �criture de l'image resultante
	EcrireImagePGM(fileName, im) ;

// liberation memoire
	free (im.buffer) ;

  return EXIT_SUCCESS ;
}

