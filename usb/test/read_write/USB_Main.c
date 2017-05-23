#include "USB_Main.h"

int USB_Main(char *ptr, 
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

// AMINE MAIN : oui c'est pour toi mon grand, implement ce main 'maison' a la
// place de l'endroi ou tu appel mon code. Merci =) 

int main()
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
    /*
    printf("\n SK = 0x%02x \n", str_r->key);
    printf(" SR = 0x%02x \n", str_r->red);
    printf(" SG = 0x%02x \n", str_r->green);
    printf(" SB = 0x%02x \n", str_r->blue);
    */
    }
    else //badkey
    {
      score--;
      str_r->red = 0xFF;
    /*
    printf("\n SK = 0x%02x \n", str_r->key);
    printf(" SR = 0x%02x \n", str_r->red);
    printf(" SG = 0x%02x \n", str_r->green);
    printf(" SB = 0x%02x \n", str_r->blue);
    */
  write_color_key(str_r,devh);
    }

    char_key = convert_uint_to_char(str_r->key);
    lettre = char_to_key(keymap, char_key);
    groupe_of_key = (int)*lettre-48;
    
    str_w = back_up_led (groupe_of_key, devh, str_r->key);
    /*
    printf(" K = 0x%02x \n", str_w->key);
    printf(" R = 0x%02x \n", str_w->red);
    printf(" G = 0x%02x \n", str_w->green);
    printf(" B = 0x%02x \n", str_w->blue);
    */
    usleep(300000);
    write_color_key(str_w, devh);
    //________________________________________________
    USB_Close(devh,0);
  }
  printf("Score = %d \n", score); 
  USB_Init_first(keymap);
  return 0;
}
