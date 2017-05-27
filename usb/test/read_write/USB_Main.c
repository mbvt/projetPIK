#include "USB_Main.h"
/*
int USB_letter(char *ptr, 
    libusb_device_handle *devh, 
    struct matrix *keymap, 
    char *bit)
{
  int score = 0;
  char *rep;
  uint16_t key = 0x00;

  rep = get_char_from_numR(keymap,ptr,bit);
  key = convert_char_to_uint(rep);
  score = read_and_write(devh, key);
  return score;
}
*/

int USB_word ( char * ptr_test, struct matrix *keymap) 
{
  libusb_device_handle *devh = NULL;
  uint16_t key = 0x00;
  char * char_key;
  char * lettre;
  int groupe_of_key = 0;
  int i = 0;
  //int len = strlen(ptr_test);
  int score = 0;
//  char *group_led; 
//  int gr_led;
  struct struct_write *str_w = malloc(sizeof(struct struct_write));
  struct struct_write *str_r = malloc(sizeof(struct struct_write));
  devh = USB_Init(0);
 str_r->key = 0x00;
   
   if( *ptr_test == ' ')
    {
      str_w->key = 0x2c;
    }
  
    else
    {
      char_key = get_numW_from_char(keymap, ptr_test);
      key = convert_char_to_uint(char_key);
      str_w->key = key;
    }
    
    while(str_r->key == 0x00)
    {
      str_r = read_to_keybord(devh);
    } 

    str_r->speed = 0x01;
    str_r->blue  = 0x00;
    str_r->green = 0x00;
    str_r->red   = 0x00;
    str_r->devh  = devh;
    if(str_r->key == str_w->key) // GOOD key
    {
      str_r->green = 0xFF;
      write_color_key(str_r,devh);
      score ++;
      i++;
    }
    else //badkey
    {
      score--;
      str_r->red = 0xFF;
      write_color_key(str_r,devh);
    }
    
    if(str_r->key != 0x2c)
    {
    char_key = convert_uint_to_char(str_r->key);
    lettre = char_to_key(keymap, char_key);
    groupe_of_key = (int)*lettre-48;
    }
    else 
    {
      groupe_of_key = 6;
    }
    str_w = back_up_led (groupe_of_key, devh, str_r->key);
    usleep(300000);
    write_color_key(str_w, devh);
    USB_Close(devh,0);
    free(str_r);
    free(str_w);
  return score;
}

int main()
{
  char *ptr_char = "azerty uiop";
  char *ptr_send;
  int score = 0;
  int res = 0;
  int i = 0;
  struct matrix *keymap;
  keymap = get_keymap("biblio");
  USB_Init_first(keymap);
  int len = strlen(ptr_char);
  while(i < len) 
  {
    ptr_send = ptr_char;
    
    res = USB_word(ptr_send, keymap);
    if(res == 1)
    {
      ptr_char ++;
      i ++;
      score ++;
    }
    else 
      score--;
    
    // les prints sont les données a affiché sur IHM 
    printf("score = %d ", score);
    printf(" |  char  = %c \n", *ptr_char);
    // fin des printf 
  }

  return 0;
}


/*
int USB_word ( char * ptr_test); 
{
  libusb_device_handle *devh = NULL;
  uint16_t key = 0x00;
  char * char_key;
  char * lettre;
  int groupe_of_key = 0;
  int i = 0;
  char *ptr_test = "azerty";
  int len = strlen(ptr_test);
  int score = 0;
  char *group_led; 
  int gr_led;
  struct struct_write *str_w = malloc(sizeof(struct struct_write));
  struct struct_write *str_r = malloc(sizeof(struct struct_write));
  struct matrix *keymap;
  keymap = get_keymap("biblio");
  USB_Init_first(keymap);
  while(i < len)
  {
    devh = USB_Init(0);
    char_key = get_numW_from_char(keymap, &ptr_test[i]);
    key = convert_char_to_uint(char_key);
    str_w->key = key;
    str_r->key = 0; 
    while(str_r->key == 0)
    {
      str_r = read_to_keybord(devh);
    } 
    str_r->speed = 0x01;
    str_r->blue  = 0x00;
    str_r->green = 0x00;
    str_r->red   = 0x00;
    str_r->devh  = devh;
    if(str_r->key == str_w->key) // GOOD key
    {
      str_r->green = 0xFF;
      write_color_key(str_r,devh);
      score ++;
      i++;
    }
    else //badkey
    {
      score--;
      str_r->red = 0xFF;
      write_color_key(str_r,devh);
    }

    char_key = convert_uint_to_char(str_r->key);
    lettre = char_to_key(keymap, char_key);
    groupe_of_key = (int)*lettre-48;
    
    str_w = back_up_led (groupe_of_key, devh, str_r->key);
    usleep(300000);
    write_color_key(str_w, devh);
    USB_Close(devh,0);
  }
  printf("Score = %d \n", score); 
  USB_Init_first(keymap);
  return 0;
}

*/
