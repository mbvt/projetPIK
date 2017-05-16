/*__________________________________________________________________
  {                                                                }
  {                         read _ right . h                       }
  {________________________________________________________________}*/


#ifndef READ_WRITE_H_
#define READ_WRITE_H_

# include "USB_Main.h"
# include "color.h"


void color_keymap_init(libusb_device_handle *devh, struct matrix *keymap);
void USB_Init_first(struct matrix *keymap);
libusb_device_handle* USB_Init(int i);
void USB_Close(libusb_device_handle *devh, int i);
int write_to_keybord( libusb_device_handle *devh);
struct struct_write* read_to_keybord(libusb_device_handle *devh);
int read_and_write(libusb_device_handle *devh, uint16_t key);

# endif 
