/* profile.c */
#include <stdlib.h>
#include <stdio.h>
#include "profile.h"
#include "dico.h"
struct profile *init_profile(int id, char *name, struct dico *dico)
{
    struct profile *profile = malloc(sizeof (struct profile));
    profile->id = id;
    profile->name = name;
    profile->dico = dico; 
    return profile;
}

struct profile *determine_profile(int age, int key, int handicap)
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
    int     id;
    char    *name;
    int     key;    
    int speed;
    if (age < 12)
    {// dico enfant
        id = 1;
        name = "child";
        dico = 2 ;
    }
    if (handicap == 1)
    {
        id = 2;
        name = "black_white";
        key = 1;//keyboard black and white
    }else if (handicap == 2)
    {
        id = 3;
        name = "visual"
        key = 2; // keyboard loupe
        
    }else if (handicap == 3)
    {
        id = 4;
        name = "motor";
        speed = 1; // modifier la rapidité
    }
    if (key == 0)
    {
        id = 5 ;
        name = "noob";
        dico = 2; // dico normale
        speed = 1;
    }else
    {
        id = 6;
        name = "normal";
        dico = 2; // dico normale
        speed = 1;
    }
       
    struct profile *profile = init_profile(id,name,dico);
    return profile;
}
