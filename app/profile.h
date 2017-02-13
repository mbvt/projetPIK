/* profile.h */
# ifndef _PROFILE_H
# define _PROFILE_H
# include "dico.h"

struct profile {
    int id;
    char *name;    
    struct dico;
};

struct profile *init_profile(int id, char *name, struct dico *dico);

struct profile *determine_profile(int age, int key, int handicap);

#endif
