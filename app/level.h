/* level.h */
# ifndef _PROJETPIK_LEVEL_H
# define _PROJETPIK_LEVEL_H

struct level {
  int id;
  int id_lvl;
  int world;
  int stage;
  int difficulty;
  int category;
};
/*
**  Init a level with the world (3) , stage(3), difficulty(3), category (atm 4)
*/
struct level *init_level (int world, int stage, int difficulty, int category,
    int id_statistic);

/*
**  get the level with the max of idNIV done = 0 user_id
*/
struct level *actual_level (int user_id )
#endif
