/* app.c */
/* Main program */

#include <err.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "level.h"

void game(char *lvl_dico);

void menu_level();

void game(char *lvl_dico )
{

  size_t i =0;
  char r;
  int WBS=0;
  struct timespec t0, t1;
  
  clock_gettime(CLOCK_MONOTONIC, &t0);
  printf("\nTapez les caracteres suivants :\n\n");
  while (i < strlen(lvl_dico))
  {
    printf("%c\n", lvl_dico[i]);
    if (lvl_dico[i] != ' ')
    {
      if (scanf(" %c",&r) == EOF)
        err(3,"Issue while get values from typing");
      if ( r == lvl_dico[i])
      {
        WBS++;
      }
      else
      {
        WBS--;
        i--;
      }

    }
    else
      WBS++;

    i++;
    printf("               WBS = %d\n",WBS);
  }
  clock_gettime(CLOCK_MONOTONIC,&t1);
  double sec = t1.tv_sec - t0.tv_sec ;
  double nsec = (double)(t1.tv_nsec - t0.tv_nsec) / 1000000000;
  double time = sec + nsec;
  
  printf("Time : %f\n",time);

  printf("Votre score : %d/%zu\n",WBS,i);
  free (lvl_dico);
}

void menu_level()
{
  printf("   ____________________________________________________________\n");
  printf("  |                                                            |\n");
  printf("  |                    Choisissez le niveau :                  |\n");
  printf("  |                                                            |\n");
  printf("  |     1) Niveau 1                                            |\n");
  printf("  |     2) Niveau 2                                            |\n");
  printf("  |     3) Niveau 3                                            |\n");
  printf("  |____________________________________________________________|\n");
  printf("\n");
//printf("Choisissez le niveau :\n1) Niveau 1\n2) Niveau 2\n3) Niveau 3\n");
  char *rep = calloc (5,sizeof(char));
  char *lvl_title = calloc (12,sizeof(char));
  
  strcat(lvl_title,"./dico/lvl");
  if (scanf("%s",rep) == EOF)
    err(3,"Issue while get values from typing");
  
  strcat(lvl_title,rep);
  
  char *lvl_dico = "";
  lvl_dico = load_dico_lvl(lvl_title);
  game(lvl_dico);
}


int main()
{
  int x = insert_lvl_1_12();
  printf("%d",x); 
/*  x = insert_lvl_13_15();
  printf("%d",x); */
//  char *str = build_one_str_from_words("./dico/lvl13");
 // char *str = get_words_from_file("./dico/lvl13");
 // printf("string generated : %s",str);
  menu_level();
  return 0;
}
