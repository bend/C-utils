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
int majuscules=0;
int minuscules=0;
int i;
printf("Entrez une chaine de caractere\n");

res=getlimitedline(chaine,strlen(chaine),stdin);



for(i=0;i<strlen(chaine);i++)
  {
    if ((chaine[i]>='A')& (chaine[i]<='Z'))
      majuscules=majuscules+1;
    if ((chaine[i]>='a')& (chaine[i]<='z'))
      minuscules=minuscules+1;
  }
  
  printf("majuscule %d\n",majuscules);
    printf("min %d\n",minuscules);
return EXIT_SUCCESS;
}




