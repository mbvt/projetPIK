#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main (void)
{
  int err;
  regex_t preg;
  const char *str_request = "abaissa";
  const char *str_regex = "([a-z]*)";

  /* (1) */
  err = regcomp (&preg, str_regex, REG_EXTENDED);
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
      match = regexec (&preg, str_request, nmatch, pmatch, 0);
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
          strncpy (site, &str_request[start], size);
          site[size] = '\0';
          printf ("%s\n", site);
          free (site);
        }
      }
      /* (5) */
      else if (match == REG_NOMATCH)
      {
        printf ("%s n\'est pas une adresse internet valide\n", str_request);
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
  puts ("\nPress any key\n");
  /* Dev-cpp */
  getchar ();
  return (EXIT_SUCCESS);
}

