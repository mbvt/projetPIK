#include "convert.h"

uint16_t convert(char *ptr)
{
  uint16_t key = 0x00;
  int cmp;
  if(*ptr <= 57)
  {
    cmp = 48;   // '0' to '9' int ascii
    while( cmp < *ptr)
    {
      key ++;
      cmp ++;
    }
  }
  else
  {
    cmp  = 65;  // 'A' to 'F' int ascii 
    key = 0x0A;
    while( cmp < *ptr)
    {   
      key ++;
      cmp ++;
    }
  }
  return key;
}

uint16_t   convert_char_to_uint(char *ptr)
{
  int i = 0;
  uint16_t result = 0x00;
  while( i < 2)
  {
    result = result + convert(ptr);
    if(i == 0)
    {
      result = result * 0x10;
    }
    i++;
    ptr++;
  }
  return result;
}    
