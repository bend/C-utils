#include <stdio.h>
#include <stdlib.h>


int main(int argc,char *argv[])
{
int i,j,c=0;

FILE *image =fopen(argv[1],"wb");
fprintf(image,"P5\n");
fprintf(image,"#CREATOR:BEN\n");
fprintf (image,"%s %s\n",argv[2],argv[3]);
fprintf(image,"255\n");

int h,l;
l=atoi(argv[2]);
h=atoi(argv[3]);

for (i=0;i<l;i++)
{
	for (j=0;j<h;j++)
	{
		fputc(c,image);
		c++;
	}
c=0;
}

fclose(image);


return EXIT_SUCCESS;
}
