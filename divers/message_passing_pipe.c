#include<stdio.h>
#include<unistd.h>
 
int main()
{
    int f[2],count,i;
    char a[20];
 
		pipe(f);
		i = fork();
		if(i==0){
			read(f[0],a,sizeof(a));
			printf("-------------\nChild process\n-------------\n");
			printf("Message from parent : \"%s\"\n",a);
			printf("Message to parent process : ");
			scanf("%s",a);
			write(f[1],a,sizeof(a));
		}
		else{
			printf("--------------\nParent Process\n--------------\n");
			printf("Enter the message to child process : ");
			scanf("%s",a);
			write(f[1],a,sizeof(a));
			sleep(1);
			read(f[0],a,sizeof(a));
			printf("--------------\nParent Process\n--------------\n");
			printf("Message from child : \"%s\"\n",a);
		}
}
