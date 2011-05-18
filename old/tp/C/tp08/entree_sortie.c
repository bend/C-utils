//---------------------------------------------------------------------------
#include "entree_sortie.h"
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

