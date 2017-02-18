/* app.c */
/* Main program */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

struct user *menu(void){

  printf("Bonjour \nProjetPik \n");

  //scanf lecture de l'option dans x
  int rep;
  char *name = malloc (256 * sizeof(char));
  char *firstname = malloc (50* sizeof (char));
  struct user *user;
  for(;;)
  {
    printf("Menu taper  : \n 1) Charger Profile\n 2) Creer Profile\n");
    scanf("%d",&rep);
    printf("vous avez entrer la valeur suivante : %d\n",rep);

    if (rep == 1)
    {
      printf("Entrez votre nom :");
      scanf("%s",name);

      printf("Entrez votre prenom :");
      scanf("%s",firstname);

      if (find_user(name,firstname,&user) == 0)
        printf("Utilisateur non trouve.\n\n");
      else
      {
        printf("Bonjour %s\n",user->firstname);
        break;
      }
    }
    else if (rep == 2)
    {
      mcq_user(&user);
      printf("Bonjour %s\n",user->firstname);
      break;
    }
    else
    {
      printf("Valeur non reconnu, ressayez.\n\n");
    }
  }
  return user;
}

void menu_level()
{

}

void game(void)
{
  FILE *file = fopen("./data/dico1", "r+");
  long fl_size;
  char *buffer;
  size_t res;

  if (file==NULL) {
    fprintf (stderr, "File error\n");
    exit (1);
  }

  fseek (file , 0 , SEEK_END);
  fl_size = ftell (file);
  rewind (file);

  buffer = (char*) malloc (sizeof(char)*fl_size);
  if (buffer == NULL) {
    fputs ("Memory error",stderr);
    exit (2);
  }

  res = fread (buffer,1,fl_size,file);
  if (res != (size_t)fl_size) {
    fputs ("Reading error",stderr);
    exit (3);
  }
  printf("%s",buffer);

  /*
   ** TODO Do the user need to type the space?
   */
  /*
     char *strtok_res;
     strtok_res = strtok(buffer, " ");
     while (strtok_res != NULL)
     {
     printf ("%s\n", strtok_res);
     size_t i =0;
     while (i != strlen(strtok_res))
     {
     printf("%c\n", strtok_res[i]);
     i++;
     }
     printf("----------\n");
     strtok_res = strtok (NULL, " ");
     }
   */

  size_t i =0;
  char r;
  int WBS;
  //char space = ' ';
  while (i != strlen(buffer))
  {
    printf("%c\n", buffer[i]);
    if (buffer[i] == ' ')
      scanf("%c",&r);
    else
      scanf(" %c",&r);

    if ((r == buffer[i]) || r == ' ')
    {
      i++;
      WBS++;
      printf("               WBS = %d\n",WBS);
    }
    else
    {
      printf("               WBS = %d\n",WBS);
      WBS--;
    }
 }



  fclose (file);
  free (buffer);
}

int main()
{
  game();
  return 0;
}
