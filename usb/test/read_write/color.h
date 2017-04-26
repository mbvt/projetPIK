#ifndef COLOR_H_
#define COLOR_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <time.h>  

struct struct_write {
  uint16_t speed;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint16_t key;
  libusb_device_handle *devh;
  };
// Definition des fonction 
void write_color_key(struct struct_write *str, libusb_device_handle *devh);
void write_color_init(libusb_device_handle *devh);
void white_color_close(libusb_device_handle *devh);
void send_data(unsigned char *data, libusb_device_handle *devh);

# endif
