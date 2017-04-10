#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SIZEOF_TREGEX 2
#define SIZEOF_WORD 1024
/*
 **
 */

char **get_args_from_file(char *f_title , size_t nbargs)
{

  FILE *file = fopen(f_title,"r+");
  char **regex= malloc( nbargs * sizeof (char*));
  long fl_size;
  size_t res;
  if ( file != NULL )
  {
    char *line = malloc(50 *sizeof(char)); /* or other suitable maximum line si    ze */
    int i = 0;
    while ( fgets ( line, 50, file ) != NULL ) /* read a line */
    {
      regex[i]=line;
      printf("Ligne %d : %s",i ,regex[i]); /* write the line */
      i++;
      line = malloc(SIZEOF_WORD *sizeof(char));
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

void build_random_str(char *chars, size_t size_wrd, size_t nb_wrd,
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
  printf("string get : %s",str);

}

int main(void)
{
  char **args_from_file= get_args_from_file("lvl1",4);
  int x = 0;
  size_t s_word = (size_t)atoi(*args_from_file);
  size_t n_word = (size_t)atoi(*(args_from_file+1));
  size_t t_word = (size_t)atoi(*(args_from_file+2));
  char *var = *(args_from_file+3);
   
  build_random_str(var,s_word,n_word,t_word);

  printf("%d",x);

  return 0;
}

