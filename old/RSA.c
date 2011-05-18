#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define OK 0
#define ERREUR 1

int evalPgcd(int a, int b){
    while(a!=b){
        if(a>b) a=a-b;
        else b=b-a;
    }
    return a;
}



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



int main(){
    int p1,p2;
    printf("Enter a prime number: ");
    scanf("%d",&p1);
    printf("Enter a second prime number: ");
    scanf("%d",&p2);
    
    int n =p1*p2;
    printf("n = %d\n",n);
    int phiden = (p1-1)*(p2-1);
    printf("phi = %d\n", phiden);
    int compteur = 0;
    int pgcd=0;
    int e=0;
    
    while(pgcd!=1){
        while(compteur==0){
            if((p1<e) && (p2<e) && (e<phiden))
                compteur=1; 
            e++;
        }
        pgcd = evalPgcd(e,phiden);
    } 
    
    printf("public key : ( %d , %d )\n",e,n);
    //char string[999];
    
    int res ;
    char chaine [9999];
    printf("text: \n");

    res=getlimitedline(chaine,strlen(chaine),stdin);
    printf("chaine[0]: %c",chaine[0]);
    
    return EXIT_SUCCESS;
}