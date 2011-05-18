
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "entree_sortie.h"
#include "traitement.h"
#include "image.h"




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
