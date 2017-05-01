#include "convert.h"

uint16_t convert(char *ptr)
{
  uint16_t key = 0x00;
  int cmp;
  int delta = 0;
  printf("-------------------\n");
  if(*ptr <= 57)
  {
    cmp = 48;   // '0' to '9' int ascii
    printf("1er \n");
    while( cmp < *ptr)
    {
      key ++;
      cmp ++;
    }
    delta = cmp - 48;
  }
  else
  {
    cmp  = 65;  // 'A' to 'F' int ascii 
    key = 0x0A;
    printf("2eme \n");
    while( cmp < *ptr)
    {   
      key ++;
      cmp ++;
    }
    delta = cmp - 48;
  }
  //printf("    key = 0x%02x \n", key);
  //printf ( "cmp = %d \n", cmp);
  //printf(" delta = %d \n", delta);
  return key;
}

uint16_t   convert_char_to_int(char *ptr)
{
  int i = 0;
  uint16_t res = 0x00;
  //char *ptr;
  //char array[3] = "6F";
  ptr = array;
  uint16_t result = 0x00;
  while( i < 2)
  {
    result = result + convert(ptr);
    printf(" result key =  0x%02x \n", result);
    if(i == 0)
    {
      result = result * 0x10;
    }
    printf("    key in = 0x%02x \n", result);
    i++;
    ptr++;
  }
  printf("    key out = 0x%02x \n", result);
  return result;
}    
