#include "image.h"
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


