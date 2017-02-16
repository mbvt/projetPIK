/* level.c */

# include <stdlib.h>

# include "level.h"

struct level *init_level (int world, int stage, int difficulty, int category,
    int id_statistic, int score_expected, long speed_expected)
{
  struct level *lvl = malloc(sizeof (struct level));
  int id_lvl = generate_idlvl(world,stage,difficulty);
  // TODO Handle erro ??
  lvl->id_lvl = id_lvl;
  lvl->world = world;
  lvl->stage = stage;
  lvl->difficulty = difficulty;
  lvl->id_statistic = id_statistic;
  lvl->score_expected = score_expected;
  lvl->speed_expected = speed_expected;

  return lvl;
}

int generate_idlvl (int difficulty, int world, int stage)
{
  int id_lvl = 0;
  if ((difficulty + world + stage) > 0)
    id_lvl = (difficulty*100) + (world*10) + stage;
  return id_lvl;
}

int get_level(int id_lvl, struct user **user)
{
  struct user *u;
  //TODO select * from lvl where id_lvl = id_lvl
  // store data in user
  // return 1 on sucess or 0
  return 1;
}

struct level *actual_level (int user_id)
{
  struct level *level;
  return level;
}

int is_succeed(int score, long speed, struct level *level);
{
  return (score > level->score_expected) && (speed < speed_expected);
}


/*
**  Generate all the level and inserting them in the database.
**  At the same moment generate also the dico for the level.
*/
#endif
