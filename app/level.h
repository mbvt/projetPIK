/* level.h */
# ifndef _PROJETPIK_LEVEL_H
# define _PROJETPIK_LEVEL_H
#include "str_mysql.h"
/*  TODO
**  This file need to include all the game's functions:
**    - load the game with the parameters appropriate (dico with the id_lvl,
**  the speed or not with Difficulty and Category , the score needed )
**    - It's maybe needed to create an user that could be the reference for all
**  the levels.
**  TODO  text_key will be for later.
**
*/
struct level {
  int id;
  int id_lvl;
  int stage;
  int difficulty;
  int category;
  int score_expected;
  long speed_expected;
  char *text;
};

/*
**  Init a level with the  stage(1-99), difficulty(3), category (atm 4)
*/
struct level *init_level (int category, int difficulty, int stage,
    int score_expected, long speed_expected, char *text);

/*
**  Generate id_lvl with the Difficulty, the World and the stage.
**  There is only 3 of each of them so the first level will be 111 (DWS)
**  This function will take in arguments D , W and S.
*/
int generate_idlvl(int category, int difficulty, int stage);

/*
**  Get the level info from the database
**  Return 1 on success or -1.
*/
int get_level(int id_lvl, struct level **lvl);

/*
**  This function will use a query to find the max idlvl of the user and verify
**  if this level have been done. It it is done then return the next level if
**  not return this one.
*/
struct level *actual_level (int user_id);

/*
**  This function will determine if the user succeed the level or not.
**  For both case it will create a new stat with actualize the attribut Done.
**  Return 1 on success or -1;
*/
int is_succeed(int score, long speed, struct level *level);

/*
**  Generate all the level and inserting them in the database.
**  At the same moment generate also the dico for the level.
*/
char  **get_args_from_file(char *f_title, size_t nbargs);

char *build_random_str (char *chars, size_t size_wrd, size_t nb_wrd);

char *load_dico_lvl(char *lvltitle, int i,int bd,struct S_MYSQL *smysql);
#endif
