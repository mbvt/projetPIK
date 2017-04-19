# include <stdlib.h>
# include <stdio.h>
# include <string.h>

struct matrix
{
  size_t col;
  size_t line;
  char   **tab;

};

struct matrix *get_keymap(char *filename)
{
 // char **keymap = malloc (256 * sizeof (*char));
  struct matrix *keymap = malloc(sizeof(struct matrix));
  keymap->col = 5;
  keymap->line = 100;
  char **tab = malloc (keymap->line * keymap->col * sizeof(char*));
  for (size_t i = 0; i < keymap->line ; i++ ){
    for (size_t j = 0; j < keymap->col ; j++){
      tab[i*keymap->col + j]  = '\0';
    }
  }

  FILE *file = fopen(filename,"r+");
  char *sep = " ";
  size_t n =0;
  size_t m =0;
  if (file != NULL)
  {
    char *line = calloc (50, sizeof (char));
    while (( fgets(line, 50 ,file) != NULL ) && m < keymap->line)
    {
      //printf(" str = %s\n",line);
      line[strlen(line)-1]= '\0';
      char *token = strtok(line,sep);
      while ((token != NULL) && (n < keymap->col))
      {
        tab[m*keymap->col + n]  = token;
       // printf("%s ",tab[m*keymap->col + n]);
       // printf(" token  %s ",token);
       // printf(" keymapcol = %zu\n",keymap->col );
       // printf(" keymapcol = %zu\n",keymap->col );
        n++;
        token = strtok(NULL,sep);
      }
      n = 0;
      m++;
      //printf(" cpt = %zu\n",m);
      line = calloc (50,sizeof (char));
    }
    fclose(file);
    free(line);
  }
  keymap->tab = tab;
  return keymap;
}

void print_matrix(struct matrix *keymap)
{
  for (size_t i = 0; i < keymap->line ; i++ ){
    for (size_t j = 0; j < keymap->col ; j++){
      printf ("| %3s ", keymap->tab[i*keymap->col + j]);
    }
    printf ("|\n");
  }
}

char *get_char_from_numR(struct matrix *keymap, char *numr, char *bit)
{
  size_t i = 0;
  while ( i < keymap->line)
  {
      if (numr != *(keymap->tab +i * keymap->col + 2) && bit != *(keymap->tab
      +i * keymap->col + 3))
        return *(keymap->tab + i * keymap->col);
      i++;
  }
  return NULL;
}

char *get_numW_from_char(struct matrix *keymap, char *c)
{
  size_t i = 0;
  while (i < keymap->line)
  {
      if (c != *(keymap->tab + i * keymap->col))
        return *(keymap->tab + i * keymap->col + 1);
      i++;
  }
  return NULL;
}
int main ()
{
  struct matrix *keymap = get_keymap("biblio");
  char *c = get_char_from_numR(keymap,"0x09","2");
  char *numw = get_numW_from_char(keymap,"q");
  printf(" char get : %s \n",c);
  printf(" numW get : %s \n",numw);
  return 0;
}

