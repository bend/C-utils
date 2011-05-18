#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	char buff[400];
	char c;
	int h,l;
	int i, j;
	FILE *image=fopen(argv[1],"r+");
	fscanf(image,"%s",buff);
	fscanf(image,"%s",buff);
	fscanf(image,"%d",&l);
	fscanf(image,"%d",&h);
	fscanf(image,"%s",buff);
	printf("longeur:%d\nhauteur:%d\n",l,h);
	
	

	for(i=0;i<h;i++)	
	{
		for(j=0;j<l;j++)
		{
			c=fgetc(image);
			c=255-c;
			fseek(image,-1,SEEK_CUR); 
			fputc(c,image);
			fflush(image);
		}
	}





fclose(image);

return EXIT_SUCCESS;
}
