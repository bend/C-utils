#include <unistd.h>
 
 int main(void)
 {
   /* ici on peut ajouter un [[malloc]] pour utiliser plus de ressource*/
   while(1) { 
     fork(); 
   } 
   return 0; 
 }

