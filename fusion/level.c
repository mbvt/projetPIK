/* level.c */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <err.h>

# include "level.h"
# include "str_mysql.h"

struct tab_chars {
  char **t_str;
  size_t len;
};

/*
** Initialization of a level.
*/
struct level *init_level (int stage, int difficulty, int category,
    int score_expected, long speed_expected, char *text)
{
  struct level *lvl = malloc(sizeof (struct level));
  int id_lvl = generate_idlvl(stage,difficulty,category);
  lvl->id_lvl = id_lvl;
  lvl->stage = stage;
  lvl->difficulty = difficulty;
  lvl->category = category;
  lvl->score_expected = score_expected;
  lvl->speed_expected = speed_expected;
  lvl->text = text;
 
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


/*
** This function get the arguments from a level file from wich we will
** get the options for the level and store them in a tab of char.
*/
char **get_args_from_file(char *f_title , size_t nbargs)
{

  FILE *file = fopen(f_title,"r+");
  char **regex= malloc( nbargs * sizeof (char*));
  if ( file != NULL )
  {
    char *line = malloc(256 *sizeof(char));
    size_t i = 0;
    while (( fgets ( line, 256, file ) != NULL ) && i < nbargs) /* read a line */
    {
      regex[i]=line;
      i++;
      line = malloc(256 *sizeof(char));
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


int compute_lvl_id(int *lvl_id)
{
    int lvl = (lvl_id[0]-1) * 9 + (lvl_id[1] -1) * 3 + lvl_id[2];
    return lvl;
}

/*
** For the levels with multiple words, we using this function to concat
** all the words in one string with a separator.
*/
char *get_words_from_file(char *f_title)
{

  FILE *file = fopen(f_title,"r+");
  char **args = get_args_from_file(f_title,6);
  size_t s_word = (size_t)atoi(*args);
  char *str = calloc (100 * s_word, sizeof(char));
  if ( file != NULL )
  {
    char *line = malloc(256 *sizeof(char));
    int i = 0;
    while ( (fgets ( line, 256, file ) != NULL) && i < 6 ) /* read a line */
    {
      i++;
      line = malloc(256 *sizeof(char));
    }

    line[strlen(line)-1]='\0';
    strcat(str,line);

    while ( fgets ( line, 256, file ) != NULL) /* read a line */
    {

      strcat(str,"-");
      line[strlen(line)-1]='\0';
      strcat(str,line);

      line = malloc(256 *sizeof(char));
    }
    fclose ( file );
    free(line);
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }
  return str;
}

struct tab_chars *str_to_tab_str(char *str,char *sep)
{
  struct tab_chars *t_chars = malloc(sizeof(struct tab_chars));
  char **t_str = calloc(100,sizeof(char*));
  char *token = strtok(str,sep);
  size_t i = 0;

  while(token != NULL)
  {
    t_str[i] = token;
    i++;
    token = strtok(NULL,sep);
  }
  t_chars->len = i;
  t_chars->t_str = t_str;
  free(t_str);
  return t_chars;
}

/*
** Build a random string with the arguments and store in a single string
*/
char *build_random_str(char *chars, size_t size_wrd, size_t nb_wrd)
{
  size_t size_str = (size_wrd+1) * nb_wrd;
  char *str = calloc( size_str , sizeof (char));
  char *tmp = calloc (1,sizeof (char));
  size_t size_chars = strlen(chars)-1;
  for (size_t i = 0; i < nb_wrd ; i++)
  {
    for (size_t y = 0; y < size_wrd ; y++)
    {
      size_t tmpcpt = rand()%size_chars;
      tmp[0] = chars[tmpcpt];
      strcat(str,tmp);
      tmp = calloc (1,sizeof (char));
    }
    strcat(str," ");
  }
  return str;
}

/*
** Get the string of all the words concatened and make a string 
** with random words.
*/
char *build_random_words_str(char *chars, size_t size_wrd, size_t nb_wrd)
{

  /* Transform a str with words concatened to a tab of words */
  struct tab_chars *t_chars = str_to_tab_str(chars,"-");
  
  char **t_str = t_chars->t_str;
  size_t len_t = t_chars->len;
  size_t size_str = (size_wrd+1) * nb_wrd;
  char *str = calloc (size_str ,sizeof (char));
  char *tmp = calloc (size_wrd ,sizeof (char));

  for (size_t i = 0; i < nb_wrd ; i++)
  {
      size_t tmpcpt = rand()%len_t;
      tmp = t_str[tmpcpt];
      strcat(str,tmp);
      tmp = calloc (size_wrd,sizeof (char));
      strcat(str," ");
  }
  return str;
}

/*
** Load the dico with the level file appropriate
*/
char *load_dico_lvl(char *lvltitle , int i, int bd, struct S_MYSQL *smysql)
{
  char **args_from_file;
  /* Load the options of the level */
  if(bd == 0 )
    args_from_file = get_args_from_file(lvltitle,7);
  else
  {
    char *id_tmp = int_to_str(i);
    char *tmp = select_level(id_tmp,smysql);
    struct tab_chars *tab_c = str_to_tab_str(tmp," ");
    args_from_file = tab_c->t_str;
    printf("%s\n",*args_from_file);
  }
  /* store the option in each apropriate var */
  size_t s_word = (size_t)atoi(*args_from_file);
  size_t n_word = (size_t)atoi(*(args_from_file+1));
  char *var;
  char *text;

  if (i < 13)
  {
    var = *(args_from_file+6);
    text = build_random_str(var,s_word,n_word);
  }
  else if(i < 16)
  {
    var = get_words_from_file(lvltitle);
    text = build_random_words_str(var,s_word,n_word);
  }
  else if (i > 15)
    err(3,"Level Not found");

  printf("  ______________________________________________________________\n");
  printf("                                                              \n");
  printf("                   -- Parametres du Niveau --                 \n");
  printf("                                                              \n");
  printf("       Taille des mots  : %zu                                   \n", s_word);
  printf("       Nombre de mots   : %zu                                   \n", n_word);
  printf("                                                              \n");
  printf("       Chaine generee   : %s                \n", text);
  printf("  ______________________________________________________________\n");
  printf("\n");

  return text;
}

