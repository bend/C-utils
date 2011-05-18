#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // vérification de la présence des paramètres sur la ligne de commande
  if (argc-1 != 2)
  {
     printf("Usage : %s taille_tableau nb_repetitions\n", argv[0]);
     exit(1);
  }

  // récupération des paramètres de la ligne de commande
  int N=atoi(argv[1]);
  int nb_repetitions=atoi(argv[2]);

  // allocation d'un tableau de taille N*N
  int* tableau=malloc(N*N*sizeof(int));

  for (int i=0; i<nb_repetitions; i++)
    // remplissage du tableau
    for (int l=0; l<N; l++)			  // pour chaque ligne
      for (int c=0; c<N; c++)			  // pour chaque colonne
	tableau[l*N+c] = l+c;			  // rand() est trop long

  /*
  int somme=0;					  // peu importe si on a un débordement
  // relectures du tableau
  for (int i=0; i<nb_repetitions; i++)
    // parcours du tableau
    for (int l=0; l<N; l++)			  // pour chaque ligne
      for (int c=0; c<N; c++)			  // pour chaque colonne
	somme += tableau[l*N+c];
  printf("somme : %d\n", somme);		  // affichage indispensable
  */

  free(tableau);

  return 0;
}
