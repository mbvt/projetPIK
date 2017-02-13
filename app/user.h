/* user.h */
#ifndef _PROJETPIK_USER_H
#define _PROJETPIK_USER_H
#include "profile.h"

struct user{
    int             id_user;
    char            *name;
    char            *firstname;
    int             age;
    int             statut;
    int             handicap;
    struct profile  *profile;

};

struct user *init_user(char *name, char *firstname, int age, int statut, 
            int handicap, struct profile *profile);

struct user *find_user(char *name, char *firstname);

struct user *mcq_user();
#endif
