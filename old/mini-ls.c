#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>




void affiche_infos_entree(char* nom_entree)
{
  /* enlever la ligne suivante et compléter */
  printf("nom entrée : %s\n", nom_entree);
}

void affiche_type_entree(unsigned char type)
{
 switch(type){
    case DT_BLK:
      printf("This is a block device \n");
      break;
    case DT_CHR:
      printf("This is a character device\n");
      break;
    case DT_DIR:
      printf("This is a directory\n");
      break;
    case DT_FIFO:
      printf("This is a named pipe (FIFO)\n");
      break;
    case DT_LNK:
      printf("This is a symbolic link\n");
      break;
    case DT_REG:
      printf("This is a regular file\n");
      break;
    case DT_SOCK:
      printf("This is a Unix domain socket\n");
      break;
    case DT_UNKNOWN:
      printf("The file type is unknown\n");
      break;
  }
}

void parcours_repertoire(char* nom_repertoire)
{
  
  DIR *dir=opendir(nom_repertoire);
  if(dir==NULL){
    perror("erreur ouverture repertoire");
    exit(0);
  }
    printf("parcours du répertoire : %s\n", nom_repertoire);
    struct dirent* entree=readdir(dir);
    while(entree!=NULL){
      printf("nom entree : %s\n",entree->d_name);
      entree=readdir(dir);
      long long int ino =entree->d_ino;
      printf("numero du inoeud : %lld\n",ino);
      affiche_type_entree(entree->d_type);
  }
  free(dir);

}

int main(int argc, char *argv[])
{
  if(argc>=2)
    parcours_repertoire(argv[1]);
  if(argc==1){
    char *dir_name;
    dir_name=get_current_dir_name();
    affiche_infos_entree(dir_name);
  }
}
