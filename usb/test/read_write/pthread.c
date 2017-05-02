#include "pthread.h"

struct queue_key_hit {
    uint16_t  ptr;
    struct    queue_key_hit *next;
};

struct str_thread {
    struct    queue_key_hit;
    int       etat_touche;
    uint16_t  key;
};

void *gestion_led(void *arg)
{
  // exttract struct 
  // test si  la touche est bonne (1) ou non (0)
  // send vert ou rouge  a  color pour colorier la touche 
  // pthread_exit(NULL);
}


// on doit ouvrir un pthread uniquement si la queue n'est pas vide 

int pthread (struct str_thread *str)
{
  struct str_thread *ptr_str = calloc (sizeof(struct str_thread), 10);
  pthread_t *th_hles = malloc ( 10 * sizeof (pthread_t));
  int cmp_queue = 0;
  int i = 0;
  while ( queue_key_hit->next != NULL)
  {
    pthread_create(th_hles + cmp_queue, NULL, gestion_led, str);
    str->queue_key_hit = (str->queue_key_hit)->next;
    cmp_queue++;
  }

  while(i <= cmp_queue)
  {
    pthread_join(*(th_hles + i), NULL);
    i++;
  }
}
