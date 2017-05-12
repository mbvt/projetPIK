//   Q U E U E  .  C

#include "queue.h"


void list_init(struct queue_key_hit *list)
{
  list->next = NULL;
}

size_t list_lent(struct queue_key_hit *list)
{
  size_t compt = 0;
  struct queue_hit_key *compt_list = list;
  while(list->next != NULL)
  {
    compt ++;
    compt = compt->list;
  }
  return compt;
}


