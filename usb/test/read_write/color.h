/*__________________________________________________________________
  {                                                                }
  {                        color . h                               }
  {________________________________________________________________}*/

#ifndef COLOR_H_
#define COLOR_H_

#include "USB_Main.h"
#include "color.h"
struct struct_zone {
  uint16_t array_key[100];
  int      len;
  };


struct struct_write {
  uint16_t   speed;
  uint16_t   red;
  uint16_t   green;
  uint16_t   blue;
  uint16_t   key;
  libusb_device_handle *devh;
  };

struct struct_key {
  uint16_t  num_w;
  uint16_t  num_r;
  char      array_nom[20];
  int       number_key;
  int       bit;
  int       groupe;
  };
/*
struct matrix {
  size_t    col;
  size_t    line;
  char    **tab;
  };
*/
// Definition des fonction 
void write_color_key(struct struct_write *str, libusb_device_handle *devh);
void write_color_init(libusb_device_handle *devh);
void white_color_close(libusb_device_handle *devh);
void send_data(unsigned char *data, libusb_device_handle *devh, int i);

struct matrix *get_keymap(char *filename); 
char *get_char_from_numR(struct matrix *keymap, char *numr, char *bit);
char *get_numW_from_char(struct matrix *keymap, char *c);
char *get_Igroup_from_key(struct matrix *keymap, char *key);
struct struct_zone *get_key_from_zone(struct matrix *keymap, char *c);
# endif
