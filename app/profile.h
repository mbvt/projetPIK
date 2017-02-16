/* profile.h */
# ifndef _PROJETPIK_PROFILE_H
# define _PROJETPIK_PROFILE_H

//TODO Do speed is really needed for the profile ?
// Or the category is enough ?? 
struct profile {
  int         id;
  int         id_category;
  int         speed;
  struct user *user;
  //lien avec les stats
};

/*
 **  Initialize a profil with an id_category given by the function determine_cat
 **  and a struct user that is linked with, then insert the profile in the
 **  database and get the id to put it in the profile id.
 */
struct profile *init_profile(int id_category, struct user *user);

/*
 **  Modify the category of the user's profile.
 **  Update the database.
 **  Return 1 on success or -1.
 */
int modify_profile(int id_category, struct user *user);

/*
 **  This function determine the category with the status of the user and if he 
 **  is handicap.
 **  Return the id_category or -1 if it fails.
 */
int determine_category(int status, int handicap);

#endif
