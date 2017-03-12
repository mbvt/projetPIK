/* app.c */
/* Main program */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "str_mysql.h"

void game(char *lvl_dico);

void menu_level();


struct user *menu(struct user *user, struct S_MYSQL *smysql){

  printf("Bonjour \nProjetPik \n");

  //scanf lecture de l'option dans x
  int rep;
  char *name = malloc (256 * sizeof(char));
  char *firstname = malloc (50* sizeof (char));
  //struct user *user = NULL;
  for(;;)
  {
    printf("Menu taper  : \n 1) Charger Profil\n 2) Creer Profil\n");
    scanf("%d",&rep);
    printf("vous avez entrer la valeur suivante : %d\n",rep);

    if (rep == 1)
    {
      printf("Entrez votre nom :");
      scanf("%s",name);

      printf("Entrez votre prenom :");
      scanf("%s",firstname);

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
      mcq_user(user, smysql);
      /*printf("Entrez votre nom :");
      scanf("%s",name);

      printf("Entrez votre prenom :");
      scanf("%s",firstname);
      
      user->firstname = firstname;
      user->name = name;
      user->age = 12;
      user->category = 1;
      user->status = 1;

      user->id_user = insert_user(user, smysql);
*/
      printf("Bonjour %s\n",user->firstname);
      break;
    }
    else
    {
      printf("Valeur non reconnue, re-essayez.\n\n");
    }
  }
  printf("FINI !\n");
  menu_level();
  return user;
}


void game(char *lvl_dico )
{

  size_t i =0;
  char r;
  int WBS;
  while (i < strlen(lvl_dico))
  {
    printf("%c\n", lvl_dico[i]);
    if (lvl_dico[i] != ' ')
      scanf(" %c",&r);
    else
      WBS++;

    if (((r==' ') || (r == lvl_dico[i])) && lvl_dico[i] != '\n')
    {
      WBS++;
    }
    else if ((lvl_dico[i] != ' ') && (r != lvl_dico[i]) )
    {
      WBS--;
      i--;
    }
    i++;
    printf("               WBS = %d\n",WBS);
  }
  printf("Votre socre : %d/%zu\n",WBS,i);
  free (lvl_dico);
}

void menu_level()
{
  printf("Choisissez le niveau :\n1) Niveau 1\n2) Niveau 2\n3) Niveau 3\n");
  int rep;
  char *lvl_title;
  scanf("%d",&rep);
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
  char *lvl_dico = load_dico_lvl(lvl_title);
  game(lvl_dico);
}


int main()
{

  struct S_MYSQL *smysql = conn_init_sql();                                     
  //char *name = "BOUVETOTI";
  //char *firstname = "Morganeee"; 

  struct user *newuser = calloc(1,sizeof(struct user)); 
  //newuser = NULL;  
  
  newuser = menu(newuser, smysql);
  /*if(!exist_user(name,firstname, smysql))                    
  {                                                                              
    newuser = calloc(1, sizeof(struct user));                        
    newuser->firstname = firstname;                                               
    newuser->name = name;   
    newuser->category = 1;
    newuser->status = 1;    
    newuser->id_user = insert_user(newuser, smysql);
    printf("id insert %d\n", newuser->id_user);    
  }                                                                             
  else                                                                          
  {   */                                                                          
    newuser = get_user(newuser->name, newuser->firstname, smysql);                        
 // }                                                                            

  if(newuser != NULL)                                                                     
    printf("Ca marche : %s, %s\n ID : %d\n", newuser->firstname, newuser->name, newuser->id_user);

  //menu_level();
  return 0;
}
