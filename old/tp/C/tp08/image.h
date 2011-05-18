#ifndef image_h
#define image_h

#define DEBUG 	0
#define OK	0
#define ERREUR	1


struct image 
//---------------------------------------------------------------------------
{
	unsigned char* buffer ; // pointeur sur lespixels de l'image
	int largeur ; // largeur de l'image
	int hauteur ; // hauteur de l'image
} ;
#endif