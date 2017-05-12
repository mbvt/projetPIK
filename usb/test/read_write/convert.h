/*______________________________________________________________
  {                                                             }
  {                 convert . h                                 }
  {_____________________________________________________________}*/
  

#ifndef CONVERT_H_
#define CONVERT_H_

#include "read_write.h"

uint16_t convert ( char *ptr);
uint16_t convert_char_to_uint(char *ptr);
char * convert_uint_to_char(uint16_t key);
#endif
