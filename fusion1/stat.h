/* stat.h */
# ifndef _PROJETPIK_STAT_H
# define _PROJETPIK_STAT_H


/*
**  Statistics will be a table in the database and each tuple is a stat.
**  Each level will record a stat and inserting it in the database.
**  It's possible to have multiple stat for one level so the var attempt is
**  usefull.
**
**  This file will also be able to get statistic of the user, like the best
**  time and score for a lvl and the best time and score of a World ,
**  Difficulty.
*/
struct stat{
  int id;
  int id_lvl;
  int attempt;
  int score;
  int score_expected;
  long speed;
  long speed_expected;
  struct user *user;
  int done;
};

/*
**  Initialize a stat for a lvl.
**  How the attempt , score_expected, speed_expected will be initialized?
**    - before the initialization
**    - then get the score and speed from the level
**    - attempt initialize in the func
*/
struct stat *init_stat(int id_lvl, int score, int score_expected,
    long speed, long speed_expected, struct user *user, int done);

/*
**  Get best time , score and user_id  from stat with an args with D,W,S and/or
**  user_id. This function can take these arguments or 0 for each of them. Then
**  depends of the case it could be a generic search(general search) or more
**  specific one.
**  It returns 1 on success or -1 if it fails and store the result in the test
**  given in args.
*/
int get_best_stat(int difficulty, int world, int stage, int user_id, struct
    stat **stat);
/*
** get the last attempt of game by a user
*/
int get_last_attempt(int id_lvl, int id_user);
#endif
