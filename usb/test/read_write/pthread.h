// P T H R E A D  . H
#ifndef PTHREAD_H_
#define PTHREAD_H_

# include "read_write.h"



struct struct_key_hit {
  uint16_t key;
  int status_key;
  libusb_device_handle *devh;
  struct struct_write *str_w;
};

void *gestion_led(void *arg);
void pthread (struct struct_key_hit *queue);
//declration programme multi thread pour allumer les led + struct 

#endif
