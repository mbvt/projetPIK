/* user.h */
#ifndef _PROFILE_H
#define _PROFILE_H
#include "profile.h"

struct user {
    char    *name;
    char    *firstname;
    int     age;
    int     statut;
    int     handicap;
    struct profile *profile;

};

struct user *init_user(char *name, char *firstname, int age, int statut, int handicap,
            struct profile *profile);

struct user *find_user(char *name, char *firstname);

struct user *mcq_user();
#endif
