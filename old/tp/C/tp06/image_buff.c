#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	FILE *f1=fopen (argv[1],"rb");
	FILE *f2=fopen (argv[2],"wb");
	if(!f1 || !f2)
		printf("probleme d'ouverture fichier");
	char entete[200];
	int l, h,bru,n,i;
	fscanf(f1,"%s",entete);
	fprintf(f2,"%s\n",entete);

	fscanf(f1,"%s",entete);
	fprintf(f2,"%s\n",entete);

	fscanf(f1,"%i",&l);
	fprintf(f2,"%i ",l);

	fscanf(f1,"%i",&h);
	fprintf(f2,"%i\n",h);

	fscanf(f1,"%i",&bru);
	fprintf(f2,"%i\n",bru);
	n=l*h;
	int *char1=(int*)malloc(n*sizeof(int));
	
	fread(char1,sizeof(char),n,f1);

	for(i=0;i<n;i++)
		char1[i]=255-char1[i];
		
	fwrite(char1,sizeof(char),n,f2);

	fclose(f1);
	fclose(f2);






return EXIT_SUCCESS;
}