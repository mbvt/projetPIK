#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *tab_regex(void)
{

  FILE *file = fopen("regexfile2","r+");
  char *regex[21];
  long fl_size;
  size_t res;
  if ( file != NULL )
  {
    char line [ 128 ]; /* or other suitable maximum line size */
    int i = 0;
    while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {
      //      printf("Ligne : %s", line); /* write the line */
      regex[i]=line;
      printf("Ligne : %s", regex[i]); /* write the line */
    }
    fclose ( file );
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }
  return *regex;

}

int r(void)
{
  int err;
//  const char *str_request = "http://www.developpez.net/forums/index.php";
 /// const char *str_regex = "(www\\.[-_[:alnum:]]+\\.[[:lower:]]{2,4})";


  /* GET AND STORE THE REGEXS IN TAB REGEX*/
  FILE *file = fopen("regexfile2","r+");
  char *regex[21];
  long fl_size;
  size_t res;
  if ( file != NULL )
  {
    char line [ 128 ]; /* or other suitable maximum line size */
    int i = 0;
    while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
    {
      //      printf("Ligne : %s", line); /* write the line */
      regex[i]=line;
      printf("Ligne : %s", regex[i]); /* write the line */
      i++;
    }
    fclose ( file );
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }

  printf("\n next round \n");
  FILE *file2 = fopen("dicowordsfr.txt","r+");
  char *dico[21];
  long fl_size2;
  size_t res2;

  printf("\n next round222 \n");
  if ( file2 != NULL )
  {
    char line [22]; /* or other suitable maximum line size */
    int i = 0;
    while ( fgets ( line, sizeof line, file2 ) != NULL ) /* read a line */
    {
      for (int y = 0; y <2; y++)
      {
        regex_t preg;
        /* (1) */
        err = regcomp (&preg, regex[y], REG_EXTENDED);
        if (err == 0)
        {
          int match;
          size_t nmatch = 0;
          regmatch_t *pmatch = NULL;

          nmatch = preg.re_nsub;
          pmatch = malloc (sizeof (*pmatch) * nmatch);
          if (pmatch)
          {
            /* (2) */
            match = regexec (&preg, line, nmatch, pmatch, 0);
            /* (3) */
            regfree (&preg);
            /* (4) */
            if (match == 0)
            {
              char *site = NULL;
              int start = pmatch[0].rm_so;
              int end = pmatch[0].rm_eo;
              size_t size = end - start;

              site = malloc (sizeof (*site) * (size + 1));
              if (site)
              {
                
                dico[i]=line;
                site[size] = '\0';
                printf ("%s\n", line);
                free (site);
              }
            }
            /* (5) */
            else if (match == REG_NOMATCH)
            {
            //  printf ("%s n\'est pas une adresse internet valide\n",&line);
            }
            /* (6) */
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

      }
      i++;
    }
    fclose ( file );
  }
  else
  {
    perror ( "regexfile" ); /* why didn't the file open? */
  }




  return 1;
}

int main(void)
{
  char x;
  x = r();
  printf("%d",x);
}

