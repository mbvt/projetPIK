/* user.c */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "user.h"

struct user *init_user(char *name, char *firstname, int age, int status, int
    handicap, int category){

  struct user *newuser =  malloc(sizeof (struct user));
  newuser->name =            name;
  newuser->firstname =       firstname;
  newuser->age =             age;
  newuser->category =        category;

  /*
   **  TODO  query to add the user in the database
   */
  return  newuser;
}

int find_user(char *name, char *firstname, struct user **user){

  /*  TODO Query select user
   **  then initialize a user
   **  return 1 on sucess or 0;
   */
  return 1;
}

int modify_user(char *name, char *firstname, int age, int status, int handicap,
    int category, struct user **user)
{
  /*  TODO Querry to modify user
   **  Check if everything is ok return 1 or 0
   */
  return 1;
}

int delete_user(struct user *user)
{
  /*  TODO Querry to delete user
   **  Check if everything is ok return 1 or 0
   */
  return 1;
}

int determine_category(int status, int handicap)
{
  /* enfant
   ** handicap
   ** black_white
   ** motor
   TODO determiner
   ** les dicos
   ** les speed
   ** les clavier couleur etc // Pour l'instant juste clavier noir et blanc
   ** est il possible d'avoir plussieur handicap + etre enfant
   */

  int category;

  if (status > 0)
    category = status
  else
    return -1;

  if (handicap > 0)
    category = handicap +2;
  //verify that category exist in database
  else
    return -1;

  return category;
}

int *mcq_user(struct user **user)
{
  struct user *user;
  struct profile *profile;
  char name[50];
  char firstname[50];
  int age;
  int keyboard;
  int handicap;
  int category;

  printf("Entrez votre nom:\n");
  scanf("%s",name);
  printf("Entrez votre prenom:\n");
  scanf("%s",firstname);
  printf("Entrez votre age:\n");
  scanf("%d",age);
  printf("Avez vous déjà utilisé un clavier ? 0/1\n");
  scanf("%d",&keyboard);

  //TODO Query select to get all the handicap possible
  // then loop printf ( handicapname, i)
  printf("Avez vous un handicap ? 0/1\n");
  printf("Lequel : Daltonien(1) Moteur(2)\n");
  scanf("%d",&handicap);

  //TODO if age > 16 status = 1 (adult) else 0
  if ((category = determine_category(status, handicap)) == -1)
    err("1", "error while determine category");

  // initialize the user
  if( find_user(name,firstname, user) == -1)
  {
    if ((user = init_user(name,firstname,age)) == NULL)
      err("1", "error while initialize user");
  }

  return 1;
}
