/* profile.h */
# ifndef _PROJETPIK_PROFILE_H
# define _PROJETPIK_PROFILE_H

# include "dico.h"

struct profile {
    int         id;
    int         id_category;
    struct user *user;
    //lien avec les stats
};

/*
**  Initialize a profil with an id_category given by the function determine_cat
**  and a struct user that is linked with, then insert the profile in the 
**  database.
*/
struct profile *init_profile(int id_category, struct user *user);

/*
**  Modify the category of the user's profile.
**  Update the database.
**  Return 1 on success or -1.
*/
int modify_profile(int id_category, struct user *user);

/*
**  This function determine the category with the status of the user, if he is
**  gets to use a keyboard and if he is handicap.
**  Return the id_category or -1 if it fails.
*/
int determine_category(int status, int key, int handicap);

#endif
