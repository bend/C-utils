#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CDTHEQUE "test.txt" // nom du fichier structures
#define OK 0
#define ERREUR 1
#define TAILLE_CHAINE 33 

//---------------------------------------------------------------------------
struct CD
//---------------------------------------------------------------------------
{ 
	char interprete[TAILLE_CHAINE];	
	char titre[TAILLE_CHAINE];
	int annee;
};

typedef struct CD tCD ;
 
//---------------------------------------------------------------------------
int getlimitedline(char*buf, int size, FILE* f)
//---------------------------------------------------------------------------
// Pascal Bertolino 2005
// lit une ligne du fichier f
// met dans buf les size-1 premiers caracteres maxi
// jette les suivants s'ils existent
// enleve le '\n' de la fin s'il y est
// marche avec les chaines vides
//---------------------------------------------------------------------------
{
	char trash[64] ;  // chaine poubelle
	char* res ;		// retour de la fonction fgets
		
	res = fgets(buf, size, f) ; // recupere le debut dans buf
	if (!res)
		return ERREUR ;

	if (strchr(buf, '\n') == NULL) 
	{		// on n'a pas lu le RC donc on n'a pas tout lu
		do // on jette la suite
		{
			res = fgets(trash, 64, f) ;
			if (res == NULL)
				return ERREUR ;
			//printf("*jette:%s*\n", trash) ;		
		}
		while (strchr(trash, '\n') == NULL) ;
	}
	else
	{
		*strchr(buf, '\n') = '\0' ; // remplace '\n' par '\0'
	}
		
	return OK ;	
}

//---------------------------------------------------------------------------
void LitCDClavier(tCD* disquePtr) 
//---------------------------------------------------------------------------
// rien � retourner, on suppose que le clavier fonctionne :-)
{
	printf("Interprete : "); 
	getlimitedline(disquePtr->interprete, 32, stdin);
	printf("\nTitre : ");
	getlimitedline(disquePtr->titre, 32, stdin);
	printf("\nAnnee: ");
	scanf("%d",&disquePtr->annee);
	printf("\n");

}
//---------------------------------------------------------------------------
void AfficheEntete() 
//---------------------------------------------------------------------------
// rien � retourner, on suppose que l'�cran fonctionne :-)
{
	printf("\n") ;
	printf("=========================================================================\n") ;
	printf("No  " ) ;
	printf("%-32s", "Interprete") ;	// garantit 32 car cadre's a gauche
	printf("%-32s", "Titre") ;
	printf("%s\n", "Annee") ;
	printf("=========================================================================\n") ;
}

//---------------------------------------------------------------------------
void AfficheCD(tCD disque, int k) 
//---------------------------------------------------------------------------
// rien � retourner, on suppose que l'�cran fonctionne :-)
{	
	printf("%-4d",k);
	printf("%-32s", disque.interprete) ;	// garantit 32 car cadre's a gauche
	printf("%-32s", disque.titre) ;
	printf("%d\n", disque.annee) ;
}

// dans les 2 fonctions ci-dessous, chaque difclose(f);sque est ecrit/lu dans le
// fichier comme 3 lignes termin�es par un CR
// c'est lourd au niveau code, mais il n'y a pas de place perdue
// dans le fichier
//---------------------------------------------------------------------------
int EcritCD(FILE* f, tCD disque)
//---------------------------------------------------------------------------
// retourne OK si �criture OK, ERREUR sinon
{

	if(fprintf(f,"%s\n",disque.titre)==0||fprintf(f,"%s\n",disque.interprete)==0||
		fprintf(f,"%d\n",disque.annee)==0);
		return ERREUR;
	return OK ;
}

//---------------------------------------------------------------------------
int LitCDFichier(FILE* f, tCD* disquePtr)
//---------------------------------------------------------------------------
// retourne OK si lecture OK, ERREUR sinon
{
	if (fscanf(f,"%s",disquePtr->titre)==0||fscanf(f,"%s",disquePtr->interprete)==0||
		fscanf(f,"%d",&disquePtr->annee)==0)
		return ERREUR;

	return OK ;
}

//---------------------------------------------------------------------------
