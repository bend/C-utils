#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void consulter()
{
   int a;
   printf("tapez 1 pour voir le montant des depenses du mois\ntapez 2 pour voir le descriptif des depenses\n");
   scanf("%d",&a);
  switch(a)
   {
      case 1:
      {
         FILE *fdepense= fopen("montant_depenses.dat","rb");//budget depenses reste
         char dep[6];
         char buff[6];
         char res[6];
         fscanf(fdepense,"%s",&*buff);
         fscanf(fdepense,"%s",&*dep);
         fscanf(fdepense,"%s",&*res);
         printf("le montant total de vos depenses est de %s € \n",dep);
         printf("il reste %s€ de votre budget initial\n",res);
         fclose(fdepense);
         break;
      }
      case 2:
      {
         char a[30];
         //int i=1;
         FILE *fdescriptif= fopen("descriptif_depenses.dat","rb");
            if (!fdescriptif)
               printf("erreur\n");
            while(!feof(fdescriptif))
              {
               fscanf(fdescriptif,"%s",&*a);
               printf("Date : %s\n",a);
               fscanf(fdescriptif,"%s",&*a);
               printf("Objet : %s\n",a);
               fscanf(fdescriptif,"%s",&*a);
               printf("Montant : %s €\n",a);
               //i++;
               }
 
         fclose(fdescriptif);
         break;
      }
   }
   
}


void enregistrer()
{
et1:{
      char date[10];
      char objet[99];
      char montant[6];
      char somme[6];
      char budget[6];
      char v[2];
      int s,m;
      FILE *fenregistrer = fopen("descriptif_depenses.dat","ab");
      printf("Entrez la date de la depense faite\n");
      scanf("%s",&*date);
      printf("entrez l'objet de la depense\n");
      scanf("%s",&*objet);
      printf("entrez le montant de la depense\n");
      scanf("%s",&*montant);printf("\n");
      printf("Date : %s\nObjet : %s\nmontant : %s\n",date,objet,montant);
      printf("Les donnees sont-elles correctes? (O/N)\n");
et2:{
      scanf("%s",&*v);
      if(v[0]=='N')
      {
         goto et1;
      }
      if(v[0]!='O' && v[0]!='N')
      {
         printf("mauvaise saisie,recommencez\n");
         goto et2;
      }
      fprintf(fenregistrer,"%s\n%s\n%s\n",date,objet,montant);
      fclose(fenregistrer);
      FILE *fdepenses= fopen("montant_depenses.dat","rb");
      fscanf(fdepenses,"%s",&*budget);//budget ne change pas
      fscanf(fdepenses,"%s",&*somme);//somme change
      //fscanf(fdepenses,"%s",&*reste);//reste = budget-somme
      fclose(fdepenses);
      s=atoi(somme);
      m=atoi(montant);
      s=s+m;
      int b=atoi(budget);
      int reste = (b-s);
      FILE *fdepenses2= fopen("montant_depenses.dat","wb");
      fprintf(fdepenses2,"%s\n",budget);
      fprintf(fdepenses2,"%d\n",s);
      fprintf(fdepenses2,"%d\n",reste);
      fclose(fdepenses2);
      printf("donnees enregistrées\n");
      }
      }
   printf("voulez-vous enregistrer une nouvelle depense(O/N)?");
et5:
   {
   char u[2];
   scanf("%s",&*u);
   if (u[0]=='O')
     goto et1;
   if (u[0]!='O' && u[0]!='N')
   {
      printf("mauvaise saisie recommencez!\n");
      goto et5;
   }
   }
}



void new_month()//renomme les ancien fichier a la date actuelle et cree les nouveaux
{
et3:{
   char a[30]={"montant_du_"};
   char b[30];
   char c[30]={"descriptif_du_"};
   int i,j;
   printf("entrez la date de l'ancien compte(mois-annee),0 si il n'existait pas de mois\n");
   scanf("%s",&*b);
   int z=atoi(b);
   if(z==0)
      goto et4;
   i=strlen(a);
   for(j=0;j<strlen(b);j++)
   {
      a[i]=b[j];
      i++;
   }
   if(rename("montant_depenses.dat",a))
   {
      printf("erreur de renomage du fichier\n");
      goto et3;
   }
   i=strlen(c);
   for(j=0;j<strlen(b);j++)
   {
      c[i]=b[j];
      i++;
   }
   if(rename("descriptif_depenses.dat",c))
   {
      printf("erreur de renomage du fichier\n");
      goto et3;
   }
et4:
   rename("descriptif_depenses.dat",c);
   FILE *fdescriptif =fopen("descriptif_depenses.dat","wb");
   FILE *fmontant =fopen("montant_depenses.dat","wb");
   if(!fdescriptif || !fmontant)
      printf("erreur de creation du fichier\n");
   if(fdescriptif && fmontant)
      printf("fichiers creés\n");
   printf("entrez le budget mensuel\n");
   int mensuel;
   scanf("%d",&mensuel);
   fprintf(fmontant,"%d\n",mensuel);
   fclose(fdescriptif);
   fclose(fmontant);
   }
}

int main ()/*rajouter encore le cryptage des donnees ainsi que un mot de passe utilisateur et une gestion du budget(budget au debut du mois - somme des depenses);(1ere ligne:budget,2 eme depenses, 3eme reste*/
{
   int choix;
   printf("tapez 1 pour une consultation de compte\ntapez 2 pour enregistrer une nouvelle depense\ntapez 3 pour debuter un nouveau mois\ntapez 0 pour quitter le programme\n");
   scanf("%d",&choix);
   switch (choix)
   {
      case 2:
         enregistrer();
         break;
      case 1:
         consulter();
         main();
         break;
      case 3:
         new_month();
         break;
      case 0:
         return EXIT_SUCCESS;
      default:
         printf("choix inexistant\n");
         main();
         break;
   }
   return EXIT_SUCCESS;
}
