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

uint16_t   convert_char_to_uint(char *ptr)
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

char * convert_uint_to_char(uint16_t key)
{
  uint16_t save = 0x00;
  uint16_t cmp = 0x00;
  char array_rep [4] = {'0', 'x'};
  char array_comp [16] =
  {'0', '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  int i = 0;
  save = key % 0x10;
  while (cmp != save)
  {
    i++;
    cmp = cmp + 0x01;
  }
  array_rep[3] = array_comp[i];
  i = 0;
  cmp = 0;
  save = key / 0x10;
  while (cmp != save)
  {
    cmp = cmp + 0x01;
    i ++;
  }
  array_rep[2] = array_comp[i];
  return array_rep;
}
