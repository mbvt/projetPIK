/*__________________________________________________________________
  {                                                                }
  {                         USB _ MAIN . h                         }
  {________________________________________________________________}*/


#ifndef USB_MAIN_H_
#define USB_MAIN_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>
#include <time.h>
#include <string.h>

struct matrix {
  size_t col;
  size_t line;
  char **tab;
  };

#include "read_write.h"
#include "color.h"
#include "script.h"
#include "convert.h"
//#include "tools_converts.h"

#endif 
