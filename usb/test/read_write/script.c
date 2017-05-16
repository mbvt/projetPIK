# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "color.h"

//_______________________________________________________________________
struct matrix *get_keymap(char *filename)
{
  struct matrix *keymap = malloc(sizeof(struct matrix));
  keymap->col = 6;
  keymap->line = 89;
  char **tab = malloc (keymap->line * keymap->col * sizeof(char*));
  for (size_t i = 0; i < keymap->line ; i++ )
  {
    for (size_t j = 0; j < keymap->col ; j++)
    {
      tab[i*keymap->col + j]  = '\0';
    }
  }

  FILE *file = fopen(filename,"r");
  char *sep = " ";
  size_t n = 0;
  size_t m = 0;
  if (file != NULL)
  {
    char *line = calloc (50, sizeof (char));
    while (( fgets(line, 50 ,file) != NULL ) && m < keymap->line)
    {
      line[strlen(line)-1]= '\0';
      char *token = strtok(line,sep);
      while ((token != NULL) && (n < keymap->col))
      {
        tab[m*keymap->col + n]  = token;
        n++;
        token = strtok(NULL,sep);
      }
      n = 0;
      m++;
      line = calloc (50,sizeof (char));
    }
    fclose(file);
    free(line);
  }
  keymap->tab = tab;
  return keymap;
}
  /*
   void print_matrix(struct matrix *keymap)
   {
   for (size_t i = 0; i < keymap->line ; i++ ){
   for (size_t j = 0; j < keymap->col ; j++){
   printf ("| %3s ", keymap->tab[i*keymap->col + j]);
   }
   printf ("|\n");
   }
   }
 */

//_____________________________________________________________________
char *get_char_from_numR(struct matrix *keymap, char *c, char *bit)
{
  size_t i = 0;
  while ( i < keymap->line)
  {
    if (*c == *(*(keymap->tab +i * keymap->col)) && *bit == *(*(keymap->tab
          +i * keymap->col + 3)))
        {
          printf("TROUVER = %s \n", *(keymap->tab + i * keymap->col));
          return *(keymap->tab + i * keymap->col + 2);
        }
    i++;
  }
  return NULL;
}

//_______________________________________________________________________
char *get_numW_from_char(struct matrix *keymap, char *c)
{
  size_t i = 0;
  while (i < keymap->line)
  {
    if (c != *(keymap->tab + i * keymap->col))
      {
        return *(keymap->tab + i * keymap->col + 1);
      }
    i++;
  }
  return NULL;
}

//_______________________________________________________________________
char *get_Igroup_from_key(struct matrix *keymap, char *key)
{
  size_t i = 0;
  while (i < keymap->line)
  {
    if (*key == *(*(keymap->tab + i * keymap->col + 1)))
      {
        return *(keymap->tab + i * keymap->col + 5);
      }
    i++;
  }
  return NULL;
}


//_______________________________________________________________________
struct struct_zone * get_key_from_zone(struct matrix *keymap, char *c)
{
  size_t i = 0;
  int j = 0;
  char *rep;
  uint16_t key;
  uint16_t *array_key;
  struct struct_zone *str = malloc(sizeof(struct struct_zone));
  array_key = calloc(sizeof(*array_key),100);
  while( i < 89)
  {
    if ( *c == *(*(keymap->tab + i * keymap->col + 5)) )
      {
        rep = *(keymap->tab + i * keymap->col + 1);
        key = convert_char_to_uint(rep);
        array_key[j] = key;
        j++;
      }
      i++;
  }
  str->len = j;
  int cmp = 0;
  while ( cmp < j)
  {
    str->array_key[cmp] = array_key[cmp];
    cmp++;
  }
  return str;
}

