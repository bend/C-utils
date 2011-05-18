#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include "test.h"

int main()
{
struct tm *tb;
time_t t;
tb = localtime(&t);
time(&t);
printf("la date est %s\n",ctime(&t));
// printf("Le numéro du mois est: %d\n",tb->tm_mon);
// printf("Le numero de annee est %d\n",tb->tm_year);
int month = tb->tm_mon;
int year = tb->tm_year;
printf("%d,%d\n",month,year);
test();


// char d[30]={"montant_du_11-O5"};
// printf("%s\n",d);
// 
// char e[30];
// int j=11;;
// int i;
//    for(i=0;i<5;i++)
//    {
//       if(j!=13)
//       {
//          e[i]= d[j];
//          j++;
//       }
//       else if(j==13)
//       {
//          i--;
//          j++;
//       }
//    }
// 
// printf("%s\n",e);

// if (year)

return EXIT_SUCCESS;

}



