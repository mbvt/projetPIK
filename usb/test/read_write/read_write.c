#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <time.h>

#include "read_write.h"

//_______________ C O L O R  -  K E Y  -  I N I T ________________
void color_keymap_init(libusb_device_handle *devh, struct matrix *keymap)
{
  int len = 0;
  int i = 0;
  
  
  char array_group[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

                                //  R     G     B
  uint16_t array_color [9][3] = { {0x00, 0x00, 0xFF}, //1 = Bleu
                                  {0x00, 0xFF, 0xB4}, //2 = Vert deau
                                  {0xFF, 0xFF, 0x00}, //3 = Jaune
                                  {0xFE, 0x77, 0x00}, //4 = Orange
                                  {0xA5, 0x00, 0xFE}, //5 = Violet
                                  {0xFF, 0x00, 0xCA}, //6 = Rose
                                  {0x65, 0x00, 0x01}, //7 = Bordaux
                                  {0xFF, 0x00, 0x00}, //8 = Rouge
                                  {0x00, 0xFF, 0x00}  //9 = Verre
                                };

  struct struct_write *str_w = calloc(sizeof(struct struct_write),9);

  for (; i < 9; i++)
  {
    str_w[i].red   = array_color   [i][0];
    str_w[i].green = array_color   [i][1];
    str_w[i].blue  = array_color   [i][2];
    str_w[i].speed = 0x01;
    str_w[i].devh  = devh;
  }

  i = 0;
  char *char_num_zone;
  struct struct_zone *str = malloc(sizeof(struct struct_zone));
  //now init all the key by group
    while(i < 10)
    {
      char_num_zone = &array_group[i];
      //printf(" char num zone = '%c' \n", *char_num_zone);
      str = get_key_from_zone(keymap, char_num_zone); 
      while( len < str->len)
      {
        str_w[i].key = str[0].array_key[len]; 
        write_color_key(&str_w[i],devh);
        len ++;
      }
      len = 0;
      i++;
      //printf("____________________________________________\n");
    }
  
  free(str);
}
//_______________ U S B  -  F I R S T  -  I N I T ________________
void USB_Init_first(struct matrix *keymap)
{
  //init libusb to with on the keybord just one time
  libusb_device_handle  *devh = NULL;
  uint16_t  PRODUCT_ID = 0xc330;
  uint16_t VENDOR_ID = 0x046d;
  int res = 0;
  int i = 0;
  res = libusb_init(NULL);
  if(res < 0)
    fprintf(stderr, "Error init libusb: %s\n", libusb_error_name(res));
  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  for (int if_num = 0; if_num < 2; if_num++) 
  {
    if (libusb_kernel_driver_active(devh, if_num)) 
      libusb_detach_kernel_driver(devh, if_num);
    res = libusb_claim_interface(devh, if_num);
  }

  // color keymap with respectiv zone 
  //while(i < 10)
  //{
    color_keymap_init(devh, keymap);
    i++;
  //}
  // Close libusb 
  libusb_release_interface(devh, 0);
  libusb_release_interface(devh, 1);

  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);
  
  if(devh)
    libusb_close(devh);
  libusb_exit(NULL);
}

//_____________________ U S B  -  I N I T ________________________
libusb_device_handle* USB_Init(int i)
{
  libusb_device_handle  *devh = NULL;
  uint16_t  PRODUCT_ID = 0xc330;
  uint16_t VENDOR_ID = 0x046d;
  int res = 0;

  res = libusb_init(NULL);
  if(res < 0)
    fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(res));
  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  for (int if_num = 0; if_num < 2; if_num++) 
  {
    if (libusb_kernel_driver_active(devh, if_num)) 
      libusb_detach_kernel_driver(devh, if_num);
    res = libusb_claim_interface(devh, if_num);
  }

  if(i == 1)
    write_color_init(devh);

  return devh;
}

//_____________________ U S B  -  C L O S E  ________________________
void USB_Close(libusb_device_handle *devh, int i)
{
  if (i == 1)
    white_color_close(devh);

  libusb_release_interface(devh, 0);
  libusb_release_interface(devh, 1);

  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);

  if(devh)
    libusb_close(devh);
  libusb_exit(NULL);

} 

//____________ WRITE_TO_KEYBORD_______________
int write_to_keybord (libusb_device_handle *devh)
{
  struct struct_write *str = malloc (sizeof (struct struct_write ));  
  uint16_t variable_local = 0x00;
  int rc = 0;

  //fprintf(stdout,"\n--------------\n Key :");
  //rc = scanf("%04x" , &variable_local);
  //fprintf(stdout,"\n Red :");
  //rc = scanf("%04x" , &str->red);
  //fprintf(stdout,"\n Green :");
  //rc = scanf("%04x" , &str->green);
  //fprintf(stdout,"\n Blue :");
  //rc = scanf("%04x" , &str->blue);
  //fprintf(stdout,"\n");

  str->speed = 0x01;
  str->devh = devh;
  str->key = variable_local;

  write_color_key(str, devh);

  free(str);    
  (void)rc;

  if(variable_local == 0x29)
    return 1;

  return 0;
}


//_______________ R E A D - T O - K E Y B O R D _________________
struct struct_write*   read_to_keybord(libusb_device_handle *devh)
{
  unsigned char data_read[1024];
  int size = 1024;
  int rc = 0;
  int actual_length = 0;
  int flag = 0;
  struct struct_write *str = malloc (sizeof (struct struct_write ));  

  for ( int i=0 ; i < size ; data_read[i++] = 0 );; 

  rc = libusb_bulk_transfer(devh, 0x81, data_read, 1024, &actual_length, 1);

  if(actual_length > 0)
  {
    for(int i = 0; i < actual_length; i ++)
    {
      if(data_read[i] != 0) 
      {
        str->key = data_read[i];
        flag = 1;
        fprintf(stdout,"\nKey ===> %02x \n", str->key);
      }
    }
  }
  if (flag == 0)
    str->key = 0;
  (void)rc;
  return str;
}

//---------------------------------------------------------------------
int read_and_write(libusb_device_handle *devh, uint16_t key)
{
  
  struct struct_write *str_w = malloc (sizeof (struct struct_write ));  
  str_w->key = 0; 
  while(str_w->key == 0)
  {
    str_w = read_to_keybord(devh);
  }
  
  //str_hit = color_keymap_init(devh, keymap, 1, key);
  str_w->speed = 0x01;
  str_w->blue = 0x00;
  str_w->green = 0x00;
  str_w->red = 0x00;
  str_w->devh = devh;

  if(str_w->key == key)
  {
    str_w->green = 0xFF;
    write_color_key(str_w, devh);
    free(str_w);
    return 1;
  }
  
  else
  {
    str_w->red = 0xFF;
    write_color_key(str_w, devh);
    free(str_w);
  }
  if(str_w->key == 0x2A)
      return -2;

  return -1;
}

/*
//----------------------- M A I N ---------------------------
int main()
{
  struct matrix *keymap = get_keymap("biblio");
  USB_Init_first(keymap);
  libusb_device_handle  *devh = NULL;
  int res = 0;
  int j = 0;
  //struct matrix *keymap = get_keymap("biblio");
  char *ptr = "epita";
  char * rep;
  char * bit = "2";
  uint16_t key = 0x00;
  int score = 0;
  printf("debut du test : 'epita' \n");
  int len = strlen(ptr);
  while(j < len)
  {
    printf("-----------------------------------------------------\n");
    devh = USB_Init(0);
    printf(" lettre = '%c' \n", *ptr);
    printf(" bit = '%c' \n", *bit);
    rep = get_char_from_numR(keymap,ptr,bit);
    key = convert_char_to_uint(rep);
    printf("test val key = 0x%02x \n", key);
    res = read_and_write(devh, key, keymap);
    if(res)
    {
      printf(" OK key value match \n");
      score ++;
    }
    else
    {
      printf(" KO key value not match\n");
      score --;
    }
    ptr++;
    USB_Close(devh, 0);
    j++;
  }
  
  (void)res;
  //devh = USB_Init(0);
  USB_Init_first(keymap);
  // en 1 th
  //USB_Close(devh, 0);
  return 0;
} */
//------------------- E N D _ M A I N -----------------------
