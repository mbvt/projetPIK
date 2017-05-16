#include "fork.h"


void *gestion_led(void *arg)
{
  printf("open pthread : \n { \n");
  (void)arg;
  struct struct_key_hit *str = arg;
  struct struct_write *str_w = malloc(sizeof(struct struct_write));
  str_w->key = str->key;
  str_w->speed = 0x01;
  str_w->blue = 0x00;
  str_w->green = 0x00;
  str_w->red = 0x00;
  str_w->devh = str->devh; 
  
  if(str->status_key == 1) // good key
  {
    str_w->green= 0xff;
    printf("    good key\n");
    write_color_key(str_w, str_w->devh);
    sleep(1);
  }
   
  else // bad key 
  {
    str_w->red= 0xff;
    printf("    bad key\n");
    write_color_key(str_w, str_w->devh);
  }
  
  color_keymap_init(str_w->devh, 

  //sleep(5);
  //free(str_w);
  //free(str);
  
  printf("    pthread  . . . \n } \n close pthread \n");
  pthread_exit(NULL);
}

// on doit ouvrir un pthread uniquement si la queue n'est pas vide 

void fork (struct struct_key_hit *str_hit)
{
// basic_fork.c: simple example of fork
 
 /*
  * MESSAGE is a simple wrapper around printf so that printf call display the
   * PID in front of the message
    * Must have at least 2 arguments, NULL can be used for the empty case
     */
     # define MESSAGE(fmt_, args...) printf("(%u): " fmt_, getpid(), args);
      
    return 0;
}
  pthread_t th_hles;
  pthread_create(&th_hles, NULL, gestion_led, str_hit);
  pthread_join(th_hles, NULL);
  write_color_key(str_hit->str_w, str_hit->&devh);

//end pthread 
}
