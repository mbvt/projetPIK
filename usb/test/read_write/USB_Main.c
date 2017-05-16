#include "USB_Main.h"

// int <== one char
// out ==> result

int USB_Main(char *ptr)
{
  int score = 0;
  char *rep;
  char *bit = "2";
  uint16_t key = 0x00;
  libusb_device_handle *devh = NULL;
  
  struct matrix *keymap = malloc(sizeof (struct matrix));
  keymap = get_keymap("biblio");
  
  USB_Init_first(keymap);
  devh = USB_Init(0);
  
  rep = get_char_from_numR(keymap,ptr,bit);
  key = convert_char_to_uint(rep);
  score = read_and_write(devh, key);
  
  USB_Close(devh,0);
  USB_Init_first(keymap);
  return score;
}

// AMINE MAIN : oui c'est pour toi mon grand, implement ce main 'maison' a la
// place de l'endroi ou tu appel mon code. Merci =) 

int main()
{
    printf("debut du test : 'azerty' \n");
    int res;
    int i = 0;
    char *ptr_test = "azerty";
    int len = strlen(ptr_test);
    int score = 0;
    while(i < len)
    {
      res = USB_Main(&ptr_test[i]);
      while (res == -1)
      {
        res = USB_Main(&ptr_test[i]); // trai again
        score = score - 1;
      }
      if (res == -2) //backspace
      {
        i--;
        score = score - 1;
      }
      i++;
      score = score + 1;
 //     i = len;
    }
    printf("Score = %d \n", score); 
  return 0;
}
