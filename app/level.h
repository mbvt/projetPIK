/* level.h */
# ifndef _PROJETPIK_LEVEL_H
# define _PROJETPIK_LEVEL_H

/*  TODO
**  This file need to include all the game's functions:
**    - load the game with the parameters appropriate (dico with the id_lvl,
**  the speed or not with Difficulty and Category , the score needed )
**    - It's maybe needed to create an user that could be the reference for all
**  the levels.
**
*/
struct level {
  int id;
  int id_lvl;
  int world;
  int stage;
  int difficulty;
  int category;
  int id_statistic;
  int score_expected;
  long speed_expected;
};

/*
**  Init a level with the world (3) , stage(3), difficulty(3), category (atm 4)
*/
struct level *init_level (int world, int stage, int difficulty, int category,
    int id_statistic, long  score_expected);

/*
**  Generate id_lvl with the Difficulty, the World and the stage.
**  There is only 3 of each of them so the first level will be 111 (DWS)
**  This function will take in arguments D , W and S.
*/
int generate_idlvl(int world, int stage, int difficulty);

/*
**  Get the level from the database
**  Return 1 on success or -1.
*/
int get_level();

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

#endif
