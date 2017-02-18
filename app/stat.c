/* stat.c */

# include <err.h>
# include <stdlib.h>

# include "stat.h"

struct stat *init_stat(int id_lvl, int score, int score_expected,
    long speed, long speed_expected, struct user *user, int done)
{
  struct stat *stat = malloc (sizeof (struct stat));
  stat->id_lvl =          id_lvl;
  stat->score =           score;
  stat->score_expected =  score_expected;
  stat->speed =           speed;
  stat->speed_expected =  speed_expected;
  stat->user =            user;
  stat->done =            done;

  stat->attempt =         get_last_attempt(id_lvl, user->id_user);

  return stat;
}


int get_best_stat(int difficulty, int world, int stage, int user_id, struct
    stat **stat)
{

}

int get_last_attempt(int id_lvl, int id_user){
  int x = 0;
  struct stat *stat = malloc (sizeof (struct stat));
  //TODO get last stat for this lvl by id_user
  // store the result in stat
  x = stat->attempt;
  free(stat);
  return x
}
#endif
