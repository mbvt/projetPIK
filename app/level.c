/* level.c */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "level.h"

struct level *init_level (int stage, int difficulty, int category,
    int score_expected, long speed_expected, char *text)
{
  struct level *lvl = malloc(sizeof (struct level));
  int id_lvl = generate_idlvl(stage,difficulty,category);
  // TODO Handle erro ??
  lvl->id_lvl = id_lvl;
  lvl->stage = stage;
  lvl->difficulty = difficulty;
  lvl->category = category;
  lvl->score_expected = score_expected;
  lvl->speed_expected = speed_expected;
  lvl->text = text;
  /*
   **  TODO insert data int database
   **  get the id to store int lvl->id_lvl;
   */
  return lvl;
}

int generate_idlvl (int category, int difficulty, int stage )
{
  int id_lvl = 0;
  if ((category + difficulty + stage) > 0)
    id_lvl = (category*1000) + (difficulty*100)  + stage;
  return id_lvl;
}

/*int get_level(int id_lvl, struct level **lvl)
  {
//TODO select * from lvl where id_lvl = id_lvl
// store data in level
// return 1 on sucess or 0
return 1;
}*/
/*
   struct level *actual_level (int user_id)
   {
   struct level *level = NULL;
//  TODO QUERY select last level with the user_id
//  store it in the struct level *level.
return level;
}*/

int is_succeed(int score, long speed, struct level *level)
{
  return (score > level->score_expected) && (speed < level->speed_expected);
}

char **get_args_from_file(char *f_title , size_t nbargs)
{

  FILE *file = fopen(f_title,"r+");
  char **regex= malloc( nbargs * sizeof (char*));
  if ( file != NULL )
  {
    char *line = malloc(50 *sizeof(char)); /* or other suitable maximum line si    ze */
    int i = 0;
    while ( fgets ( line, 50, file ) != NULL ) /* read a line */
    {
      regex[i]=line;
      //printf("Ligne %d : %s",i ,regex[i]); /* write the line */
      i++;
      line = malloc(50 *sizeof(char));
    }
    fclose ( file );
    free(line);
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }
  return regex;
}

char *build_random_str(char *chars, size_t size_wrd, size_t nb_wrd,
    size_t size_chars)
{
  size_t size_str = (size_wrd+1) * nb_wrd;
  char *str = calloc( size_str , sizeof (char));
  size_t cpt = 0;
  char *tmp = calloc (1,sizeof (char));
  for (size_t i = 0; i < nb_wrd ; i++)
  {
    for (size_t y = 0; y < size_wrd ; y++)
    {
      size_t tmpcpt = rand()%size_chars;
      tmp[0] = chars[tmpcpt];
      strcat(str,tmp);
      cpt += size_wrd+1;
      tmp = calloc (1,sizeof (char));
    }
    strcat(str," ");
  }
  //printf("string get : %s\n",str);
  return str;
}

// FOR NOW just return the char text of a level
// but later it will fill the level->text
char *load_dico_lvl(char *lvltitle)
{
  char **args_from_file = get_args_from_file(lvltitle,4);
  size_t s_word = (size_t)atoi(*args_from_file);
  size_t n_word = (size_t)atoi(*(args_from_file+1));
  size_t t_word = (size_t)atoi(*(args_from_file+2));
  char *var = *(args_from_file+3);

  char *text = build_random_str(var,s_word,n_word,t_word);
  printf("  ______________________________________________________________\n");
  printf("                                                              \n");
  printf("                   -- Parametres du Niveau --                 \n");
  printf("                                                              \n");
  printf("       Taille des mots  : %zu                                   \n", s_word);
  printf("       Nombre de mots   : %zu                                   \n", n_word);
  printf("       Taille du t_char : %zu                                  \n", t_word);
  printf("       t_char           : %-s", var);
  printf("                                                              \n");
  printf("       Chaine generee   : %s                \n", text);
  printf("  ______________________________________________________________\n");
  printf("\n"); 

  return text;
}

/*
 **  Generate all the level and inserting them in the database.
 **  At the same moment generate also the dico for the level.
 */
