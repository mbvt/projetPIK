#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <time.h>

#include "color.h"
#include "convert.h"
#include "read_write.h"

//_______________ C O L O R  -  K E Y  -  I N I T ________________
void color_keymap_init(libusb_device_handle *devh, struct matrix *keymap)
{
  int i = 0;
  uint16_t *ptr_array_key;
  char array_group[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

                                //  R     G     B
  uint16_t array_color [9][3] = { {0x00, 0x00, 0xFF}, //1 = Bleu
                                  {0x54, 0x29, 0x00}, //2 = Maron
                                  {0xFD, 0xF8, 0x31}, //3 = Jaune
                                  {0x00, 0xF8, 0x31}, //4 = Orange
                                  {0x34, 0x31, 0xFD}, //5 = Violet
                                  {0xFD, 0x31, 0xDA}, //6 = Rose
                                  {0x4A, 0x1A, 0x2C}, //7 = Bordaux
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
  char *char_num_zone = NULL;
  //now init all the key by group
  while(i < 10)
  {
    *char_num_zone = array_group[i];
    ptr_array_key = get_key_from_zone(keymap, char_num_zone);
    while(ptr_array_key != NULL)
    {
      str_w[i].key = *ptr_array_key;
      write_color_key(&str_w[i],devh);
      ptr_array_key++;
    }
    str_w++;
    i++;
  }
}

//_______________ U S B  -  F I R S T  -  I N I T ________________
void USB_Init_first(struct matrix *keymap)
{
  //init libusb to with on the keybord just one time
  libusb_device_handle  *devh = NULL;
  uint16_t  PRODUCT_ID = 0xc330;
  uint16_t VENDOR_ID = 0x046d;
  int res = 0;

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
  color_keymap_init(devh, keymap);
  
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

  uint16_t data_color [16] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70,
    0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xFF}; 

  struct struct_write *str = malloc (sizeof (struct struct_write ));  
  str->key = 0; 
  while(str->key == 0)
  {
    str = read_to_keybord(devh);
  }
  str->red    = data_color[rand()%15];
  str->green  = data_color[rand()%15];
  str->blue  = data_color[rand()%15];
  str->speed = 0x01;
  str->devh = devh;

  if(str->key != 0x00)
    write_color_key(str, devh);

  if(str->key == key)
  {
    free(str);
    return 1;
  }
  free(str);
  return 0;
}


//----------------------- M A I N ---------------------------
int main()
{
  struct matrix *keymap = get_keymap("biblio");
  USB_Init_first(keymap);

  libusb_device_handle  *devh = NULL;
  int res = 0;
  //struct matrix *keymap = get_keymap("biblio");
  char * ptr = "EPITA";
  char * rep;
  uint16_t key = 0x00;
  rep = ptr;
  int score = 0;
  while(ptr != NULL)
  {
    devh = USB_Init(0);
    rep = get_numW_from_char(keymap, rep);
    key = convert_char_to_uint(rep);
    printf("test val key = 0x%02x \n", key);
    ptr++;
    res = read_and_write(devh, key);
    if(res)
    {
      printf(" OK key value match");
      score ++;
    }
    else
    {
      printf(" KO key value not match");
      score --;
    }
    USB_Close(devh, 0);
  }
  
  /*
  //-----------------------------------------|
  while(res == 0)
  {
  devh = USB_Init(0);
  res = read_and_write(devh);
  USB_Close(devh, 0);
  }
   */
  //-------------------------------------------|
  (void)res;
  devh = USB_Init(0);
  USB_Close(devh, 1);
  return 0;
} 
//------------------- E N D _ M A I N -----------------------
