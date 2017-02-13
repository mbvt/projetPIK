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

struct profile *init_profile(int id, char *name, struct dico *dico);

struct profile *determine_profile(int age, int key, int handicap);

#endif
