// main final (exercice 5)
//---------------------------------------------------------------------------
#include "cdtheque1_etudiant.h"

int main()

//---------------------------------------------------------------------------
{

	FILE* f ;
	tCD disque ;
	int k = 1 ;
	char choix ;

	while (k)
	{
		printf("\nAffich | Nouv | Quit : ");
		
		scanf ("\n%c", &choix) ;
		getchar() ; // absorbe le retour chariot du scanf
		
		switch(choix)
		{
			case 'a' : case 'A':
			{
				f=fopen(CDTHEQUE,"r");
				AfficheEntete();
				while (feof(f)==0)
				{
					
					LitCDFichier(f,&disque);
					AfficheCD(disque,k);
					k++;
					
				}
				fclose(f);
				break;
			}
			case 'N' : case 'n' : 
				{
				f=fopen(CDTHEQUE,"a");
				LitCDClavier(&disque);
				EcritCD(f ,disque);
				fclose(f);
				break;
				}
				
			case 'q': case 'Q':
				k = 0;
				break;
		}
	}
	return EXIT_SUCCESS ;
}

