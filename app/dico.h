/* dico.h */

#ifndef _PROJETPIK_DICO_H
#define _PROJETPIK_DICO_H

struct dico{
  int id;
  int id_lvl;
  char *text;
  char *text_key;

};

/*
**  Initialize a dico with the id_cat and id_lvl
**  insert the dico in the database and get back the id for the struct dico
*/
struct dico *init_dico(int id_lvl);

/*
**  Create all the dico with different words
*/

#endif
