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

int is_succeed(int score, long speed, struct level *level)
{
  return (score > level->score_expected) && (speed < level->speed_expected);
}

/*
** This function get the arguments from a level file from wich we will
** the options for the level and store them in a tab of char.
*/
char **get_args_from_file(char *f_title , size_t nbargs)
{

  FILE *file = fopen(f_title,"r+");
  char **regex= malloc( nbargs * sizeof (char*));
  if ( file != NULL )
  {
    char *line = malloc(256 *sizeof(char)); /* or other suitable maximum line si    ze */
    int i = 0;
    while ( fgets ( line, 256, file ) != NULL ) /* read a line */
    {
      regex[i]=line;
      //printf("Ligne %d : %s",i ,regex[i]); /* write the line */
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
/*
** Build a random string with the arguments and store in a single string
*/
char *build_random_str(char *chars, size_t size_wrd, size_t nb_wrd)
{
  size_t size_str = (size_wrd+1) * nb_wrd;
  char *str = calloc( size_str , sizeof (char));
  size_t cpt = 0;
  char *tmp = calloc (1,sizeof (char));
  size_t size_chars = strlen(chars);
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
  // Load the options of the level
  char **args_from_file = get_args_from_file(lvltitle,3);
  
  // store the option in each apropriate var
  size_t s_word = (size_t)atoi(*args_from_file);
  size_t n_word = (size_t)atoi(*(args_from_file+1));
  char *var = *(args_from_file+2);

  char *text = build_random_str(var,s_word,n_word);
  printf("  ______________________________________________________________\n");
  printf("                                                              \n");
  printf("                   -- Parametres du Niveau --                 \n");
  printf("                                                              \n");
  printf("       Taille des mots  : %zu                                   \n", s_word);
  printf("       Nombre de mots   : %zu                                   \n", n_word);
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

int insert_lvl_1_12()
{
  for (size_t i = 1 ; i < 13 ; i++)
  {
    char *lvl_dico = calloc (15,sizeof(char));
    
    sprintf(lvl_dico,"./dico/lvl%zu",i);
    
    char **args = get_args_from_file(lvl_dico,7);
    /*
    pos for each args:
      text  : 2
      speed : 3
      score : 4
      id_diff : 5
      id_world : 6
  
    usage : 
      char *text = args+3
    */  
    printf("Label : lvl%zu\n\ntext : %s\nspeed : %s\nscore : %s\nid_diff : %s\nid_world : %s\n"
    ,i, *(args+2),*(args+3),*(args+4),*(args+5),*(args+6));
    printf("_____________________________ \n\n"); 
    free(lvl_dico);
  }
  return 0;
}

