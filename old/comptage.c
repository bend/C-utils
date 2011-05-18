#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10
#define OK 0
#define ERREUR 1

//----------------------------------------------------
int getlimitedline(char*buf, int size, FILE* f)
// Pascal Bertolino 2005
// lit une ligne du fichier f
// met dans buf les size-1 premiers caracteres maxi
// jette les suivants s'ils existent
// enleve le '\n' de la fin s'il y est
// marche aussi avec les chaines vides
//----------------------------------------------------
{
        char trash[64] ;  // chaine poubelle
        char* res ;             // retour de la fonction fgets

        res = fgets(buf, size, f) ; // recupere le debut dans buf
        if (!res)
                return ERREUR ;

        if (strchr(buf, '\n') == NULL)
        {               // on n'a pas lu le RC donc on n'a pas tout lu
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
int main()
//---------------------------------------------------------------------------
// appel getlimitedline pour lire une ligne de fichier texte sans se soucier des
// espaces ni d'autres delimiteurs
// on ne recupere que les SIZE-1 premiers caracteres maxi qui sont ranges dans
// buf qui est toujours termine' par un '\0'
//
// le fichier peut etre quelconque (FILE*) et pas seulement stdin

// bien sur comme le montre l'exemple, ca marche meme pour plusieurs saisies
// � la suite, ce qui n'est pas le cas avec fgets !!!
{





int res ;
char chaine [20];
int i;
int n;
char V[2][10]={{0},{0}};
int car;
printf("Entrez une chaine de caractere\n");

res=getlimitedline(chaine,strlen(chaine),stdin);


for (i=0;i<strlen(chaine);i++)
{
	car=chaine[i];
	for (n=0;i<10;n++)           
	{
		if (car==(V[0][n]))
		{
			V[1][n]=V[1][n]++;
			break;
		}
	else if (car!=V[0][n] && V[0][n]==0)
		{
			V[0][n]=car;
			V[1][n]=1;
			break;
		}
	}
}

for (i=0;i<strlen(chaine);i++)
{						
	if(V[1][i]!=0)
		printf("%c : %d\n",V[0][i],V[1][i]);
	
}
return EXIT_SUCCESS;
}

