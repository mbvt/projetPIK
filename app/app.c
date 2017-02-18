/* app.c */
/* Main program */

#include <stdio.h>
#include <stdlib.h>
#include "user.h"

struct user *menu(){

  printf("Bonjour \nProjetPik \n");
  printf("Menu taper  : \n 1) Charger Profile\n 2) Creer Profile\n");

  //scanf lecture de l'option dans x
  int *rep;
  *rep = 1;
  scanf("%d",rep);
  printf("vous avez entrer la valeur suivante : %d\n",*rep);
  char *name = malloc(256*sizeof (char));
  char *firstname = malloc(256*sizeof (char));
  struct user *user;

  if (*rep == 1)
  {
    printf("Entrez votre nom :");
    scanf("%s",name);

    printf("Entrez votre prenom :");
    scanf("%s",firstname);

    user = find_user(name,firstname);//-> afficher entrer nom prenom -> struct profil =
  }
  else if (*rep == 2)
  {
    user = mcq_user();

  }
  return user;

}

int main(){

  return 0;

}
