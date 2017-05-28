/*______________________________________________________________
  {                                                             }
  {                 convert . h                                 }
  {_____________________________________________________________}*/
  

#ifndef CONVERT_H_
#define CONVERT_H_

#include "USB_Main.h"

uint16_t convert ( char *ptr);
uint16_t convert_char_to_uint(char *ptr);
char * convert_uint_to_char(uint16_t key);
#endif
