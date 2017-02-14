/* profile.c */
#include <stdlib.h>
#include <stdio.h>
#include "profile.h"
#include "dico.h"
struct profile *init_profile(int id_category, struct user *user)
{
  struct profile *profile = malloc(sizeof (struct profile));
  profile->id_catefory = id_category;
  profile->user = user;
  return profile;
}

struct profile *determine_category(int status, int handicap)
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
** les clavier couleur etc
** est il possible d'avoir plussieur handicap + etre enfant
*/

  int category;

/*
** TODO category = status ??
*/
  if (status > -1)
    category = status
  else
    return -1;

  if (handicap > 0)
    category = handicap +1;
    //verify that category exist in database
  else
    return -1

  return category;
}
