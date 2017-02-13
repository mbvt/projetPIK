/* stats.h */
# ifndef _PROJETPIK_STATISTICS_H
# define _PROJETPIK_STATISTICS_H

struct stats{
  int id;
  int id_lvl;
  int score;
  int score_expected;
  long speed;
  long speed_expected;
  struct user *user;
  int attempt;
  int done;
}

#endif
