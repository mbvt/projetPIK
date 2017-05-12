#include "convert.h"

uint16_t convert(char *ptr)
{
  uint16_t key = 0x00;
  int cmp;
  //printf(" in convert %d \n", *ptr);
  if(*ptr <= 57)
  {
    cmp = 48;   // '0' to '9' int ascii
    //printf("        cmp = %d\n", cmp);
   // printf(" key = 0x%02x  et cmp = %d \n", key, cmp);
    while( cmp < *ptr)
    {
     // printf("   key = 0x%02x  et cmp = %d \n", key, cmp);
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
      //printf(" key = 0x%02x  et cmp = %d \n", key, cmp);
      key ++;
      cmp ++;
    }
  }
  return key;
}

uint16_t   convert_char_to_uint(char *ptr)
{
  uint16_t result = 0x00;
    result = result + convert(&ptr[2]);
    result = result * 0x10;
    result = result + convert(&ptr[3]);
  return result;
}    

char * convert_uint_to_char(uint16_t key)
{
  uint16_t save = 0x00;
  uint16_t cmp = 0x00;
  char *array_rep = malloc( 4 * sizeof(char));
  
  array_rep [0] = '0';
  array_rep [1] = 'x';
  
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
