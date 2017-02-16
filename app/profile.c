/* profile.c */

#include <stdlib.h>
#include "profile.h"


struct profile *init_profile(int id_category, struct user *user)
{
  struct profile *profile = malloc(sizeof (struct profile));
  profile->id_catefory = id_category;
  profile->user = user;
  return profile;
}

int modify_profile(int id_category, struct user *user)
{
  //TODO QUERY update
  // check if its done
  // return 1 or 0 if fails
  return 1;

}

int determine_category(int status, int handicap)
{
  // enfant
  // handicap
  // black_white
  // visual
  // motor
  // noob
  // normal
  // expert$


/* TODO determiner
** les dicos
** les speed
** les clavier couleur etc // Pour l'instant juste clavier noir et blanc
** est il possible d'avoir plussieur handicap + etre enfant
*/

  int category;

/*
** TODO category = status ??
*/
  if (status > 0)
    category = status
  else
    return -1;

  if (handicap > 0)
    category = handicap +2;
    //verify that category exist in database
  else
    return -1

  return category;
}


