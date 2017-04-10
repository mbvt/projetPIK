#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SIZEOF_TREGEX 7
#define SIZEOF_WORD 1024

char **tab_regex(void)
{

  FILE *file = fopen("regexfile2","r+");
  char **regex=malloc( SIZEOF_TREGEX * sizeof (char*));
  long fl_size;
  size_t res;
  if ( file != NULL )
  {
    char *line = malloc(SIZEOF_WORD *sizeof(char)); /* or other suitable maximum line size */
    //char line[21]; /* or other suitable maximum line size */
    int i = 0;
    while ( fgets ( line, SIZEOF_WORD, file ) != NULL ) /* read a line */
    {
      regex[i]=line;
      printf("Ligne %d : %s",i ,regex[i]); /* write the line */
      i++;
      //line[0] = '\0';
    //  memset(line,0,MAX_SIZEOF_WORD);
      line = malloc(SIZEOF_WORD *sizeof(char)); /* or other suitable maximum line size */
    }
    fclose ( file );
    free(line);
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }
  //printf("ligne 0 %s",regex[0]);
  //printf("ligne 1 %s",regex[1]);
  return regex;

}

int r(void)
{
  int err;

  /* GET AND STORE THE REGEXS IN TAB REGEX*/
  char **tab_r;
  tab_r = tab_regex();
  //printf("%s",tab_r[1]);
  
  
  
  char **dico= malloc (SIZEOF_TREGEX *sizeof(char*));
  for (int i =0 ; i< SIZEOF_TREGEX; i++)
  {
    dico[i] = calloc(SIZEOF_WORD , sizeof(char));
  }
  printf("\n next round \n");
  FILE *file2 = fopen("dicowordsfr.txt","r+");
  long fl_size2;
  size_t res2;
  
  printf("\n next round222 \n");
  if ( file2 != NULL )
  {
    char *line = malloc(SIZEOF_WORD* sizeof(char)); /* or other suitable maximum line size */
    /*  for each word */
    while ( fgets ( line, sizeof line, file2 ) != NULL ) /* read a line */
    {
      /* for each regex  */
      for (int y = 0; y < SIZEOF_TREGEX; y++)
      {
         printf("%s",tab_r[y]);
        regex_t preg;
        /* compile the regex */
        err = regcomp (&preg, tab_r[y], REG_EXTENDED);
        if (err == 0)
        {
          int match;
          size_t nmatch = 0;
          regmatch_t *pmatch = NULL;

          nmatch = preg.re_nsub;
          pmatch = malloc (sizeof (*pmatch) * nmatch);
          if (pmatch)
          {
            /* try to match */
            match = regexec (&preg, line, nmatch, pmatch, 0);
            /* free the regex compiled */
            regfree (&preg);
            /* (4) */
            if (match == 0)
            {
              char *str = NULL;
              int start = pmatch[0].rm_so;
              int end = pmatch[0].rm_eo;
              size_t size = end - start;

              str = malloc (sizeof (char) * (size + 1));
              if (str)
              {
                strncpy(str,&line[start],size);
                strcat(str," ");
                //printf ("%s\n", str);
                strcat(dico[y],str);
                printf ("%s\n", dico[y]);
                free (str);
              }
            }
            /* (5) */
            else if (match == REG_NOMATCH)
            {
            //  printf ("%s n\'est pas une adresse internet valide\n",&line);
            }
            /* ERROR HANDLE */
            else
            {
              char *text;
              size_t size;

              /* (7) */
              size = regerror (err, &preg, NULL, 0);
              text = malloc (sizeof (*text) * size);
              if (text)
              {
                /* (8) */
                regerror (err, &preg, text, size);
                fprintf (stderr, "%s\n", text);
                free (text);
              }
              else
              {
                fprintf (stderr, "Memoire insuffisante\n");
                exit (EXIT_FAILURE);
              }
            }
          }
          else
          {
            fprintf (stderr, "Memoire insuffisante\n");
            exit (EXIT_FAILURE);
          }
        }
      line= malloc(SIZEOF_WORD * sizeof(char));
      }
    }
    fclose ( file2 );
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }
  return 1;
}

int main(void)
{
  
  int x;
  x = r();
  printf("%d",x);
  
  /*
  char **x;
  x = tab_regex();
  printf("%s",x[0]);
  printf("%s",x[1]);
  strcat(x[0],"YOYOOYYO");

  printf("%s",x[0]);
  */
}

