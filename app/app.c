/* app.c */
/* Main program */

#include <err.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "str_mysql.h"
#include "level.h"

void game(char *lvl_dico);

void menu_level();


struct user *menu(struct user *user, struct S_MYSQL *smysql){
  printf("   ____________________________________________________________\n");
  printf("  |                                                            |\n");
  printf("  |                 BIENVENUE SUR LE PROJET PIK                |\n");
  printf("  |____________________________________________________________|\n");
  printf("  |                                                            |\n");
  printf("  |                                         --  by ChocAPI-K   |\n");                   
  printf("  |____________________________________________________________|\n");
  printf("\n");

  //scanf lecture de l'option dans x
  int rep;
  char *name = malloc (256 * sizeof(char));
  char *firstname = malloc (50* sizeof (char));
  for(;;)
  {
    printf("   ____________________________________________________________\n");
    printf("  |                                                            |\n");
    printf("  |                        -- MENU --                          |\n");
    printf("  |                                                            |\n");
    printf("  |     1) Charger un profil                                   |\n");
    printf("  |     2) Creer un profil                                     |\n");
    printf("  |____________________________________________________________|\n");
    printf("\n");

    //printf("\nVeuillez taper : \n 1) Charger Profil\n 2) Creer Profil\n");

    if (scanf("%d",&rep) == EOF)
      err(3,"Issue while get values from typing");

    if (rep == 1)
    {
      printf("Entrez votre nom :\n");
      if (scanf("%s",name) == EOF)
        err(3,"Issue while get values from typing");


      printf("Entrez votre prenom :\n");

      if (scanf("%s",firstname) == EOF)
        err(3,"Issue while get values from typing");
      printf("\n");

      if (!exist_user(name,firstname,smysql))
        printf("Utilisateur non trouve.\n\n");
      else
      {     
        user = get_user(name, firstname, smysql);
        printf("Bonjour %s\n",user->firstname);

        break;
      }
    }
    else if (rep == 2)
    {
      user = mcq_user(user, smysql);
      printf("Bonjour %s\n",user->firstname);
      break;
    }
    else
    {
      printf("Valeur non reconnue, re-essayez.\n\n");
    }
  }
  menu_level();
  return user;
}


void game(char *lvl_dico )
{

  size_t i =0;
  char r;
  int WBS=0;

  printf("\nTapez les caracteres suivants :\n\n");
  while (i < strlen(lvl_dico))
  {
    printf("%c\n", lvl_dico[i]);
    if (lvl_dico[i] != ' ')
    {
      if (scanf(" %c",&r) == EOF)
        err(3,"Issue while get values from typing");
      if ( r == lvl_dico[i])
      {
        WBS++;
      }
      else
      {
        WBS--;
        i--;
      }

    }  
    else
      WBS++;

    i++;
    printf("               WBS = %d\n",WBS);
  }
  printf("Votre score : %d/%zu\n",WBS,i);
  free (lvl_dico);
}

void menu_level()
{
    printf("   ____________________________________________________________\n");
    printf("  |                                                            |\n");
    printf("  |                    Choisissez le niveau :                  |\n");
    printf("  |                                                            |\n");
    printf("  |     1) Niveau 1                                            |\n");
    printf("  |     2) Niveau 2                                            |\n");
    printf("  |     3) Niveau 3                                            |\n");
    printf("  |____________________________________________________________|\n");
    printf("\n");
//printf("Choisissez le niveau :\n1) Niveau 1\n2) Niveau 2\n3) Niveau 3\n");
  int rep;
  char *lvl_title = "";
  if (scanf("%d",&rep) == EOF)
    err(3,"Issue while get values from typing");

  switch (rep) {
    case 1:
      lvl_title = "./dico/lvl1";
      break;
    case 2:
      lvl_title = "./dico/lvl2";
      break;
    case 3:
      lvl_title = "./dico/lvl3";
      break;
  }
  char *lvl_dico = "";
  lvl_dico = load_dico_lvl(lvl_title);
  game(lvl_dico);
}


int main()
{
  struct S_MYSQL *smysql = conn_init_sql();                                     

  struct user *newuser = calloc(1,sizeof(struct user)); 

  newuser = menu(newuser, smysql);                        

/*  char *s = NULL;
  char *lvl_title = "./dico/lvl2";


  s = load_dico_lvl(lvl_title);

   printf("%s\n", s);
*/  /* if(newuser != NULL)                                                                     
     printf("Ca marche : %s, %s\n ID : %d\n", newuser->firstname, newuser->name, newuser->id_user);
   */
  return 0;
}
