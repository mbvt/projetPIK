/* user.c */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "user.h"

struct user *init_user(char *name, char *firstname, int age, int status, int
    handicap, struct profile *profile){

  struct user *newuser =  malloc(sizeof (struct user));
  newuser->name =            name;
  newuser->firstname =       firstname;
  newuser->age =             age;
  newuser->profile =         profile;

  //char profname[] = *(profile->name);

  //TODO Remplace next lines with Database query
  char append[2];
  FILE *file = fopen("~/data/user","w");
  char *line = malloc(256*sizeof(char));
  strcat(line,name);
  strcat(line,"/");
  strcat(line,firstname);
  strcat(line,"/");
  sprintf(append,"%d",age);
  strcat(line,append);
  strcat(line,"/");
  strcat(line,profname);
  fwrite(line,1,sizeof(line),file);
  fclose(file);

  return  newuser;
}

int find_user(char *name, char *firstname, struct user **user){

  //TODO Query select user
  // then initialize a user
  FILE *file = fopen("~/data/user","r");
  struct user *user = malloc(sizeof (struct user));
  char line[128];
  int i = 0;
  int find = 0;
  while(fgets(line, sizeof (line), file) != NULL && find == 0 )
  {
    //for each elmt seperate by delimiter
    // stocker dans liste tout la ligne
    // si l.name = name && l.firstname = firstname
    // init_user avec les elmt de la liste retourné le user.
    printf("line %d : %s",i,line);
    i++;
  }

  fclose(file);
  return user;
}

int *mcq_user(struct user **user)
{
  struct user *user;
  struct profile *profile;
  char name[50];
  char firstname[50];
  char age[3];
  int keyboard;
  int handicap;
  int category;

  printf("Entrez votre nom:\n");
  scanf("%s",name);
  printf("Entrez votre prenom:\n");
  scanf("%s",firstname);
  printf("Entrez votre age:\n");
  scanf("%s",age);
  printf("Avez vous déjà utilisé un clavier ? 0/1\n");
  scanf("%d",&keyboard);

  //TODO Query select to get all the handicap possible
  // then loop printf ( handicapname, i)
  printf("Avez vous un handicap ? 0/1\n");
  printf("Lequel : Daltonien(1) Moteur(2)\n");
  scanf("%d",&handicap);

  if ((category = determine_category) == -1)
    err("1", "error while determine category");

  // créer le profile
  profile = init_profile(category,user);

  // initialize the user
  if( find_user(name,firstname, user) == -1)
  {
    if ((user = init_user(name,firstname,age,profile)) == NULL)
      err("1", "error while initialize user");
  }

  return 1;
}
