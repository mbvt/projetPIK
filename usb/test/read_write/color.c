# include "color.h"

//__________________ WRITE ONE KEY _____________________

void write_color_key(struct struct_write *str, libusb_device_handle *devh)
{

  unsigned char data_commit [] = { 0x11, 0xff, 0x0c, 0x5a, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  unsigned char data [] = { 0x12, 0xff, 0x0c , 0x3a,
    0x00, str->speed, 0x00, 0x0e, 
    str->key, str->red, str->green, str->blue, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  send_data(data, devh, 1);
  send_data(data_commit, devh, 0); 
}


//_____________ WHITE WHEN INIT DEVICE ___________________

void write_color_init(libusb_device_handle *devh)
{
unsigned char commit [] = {   0x11, 0xFF, 0x3c, 0x5a, 
    0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x88,
    0x00, 0x00, 0x00, 0x00,
  };


  unsigned char all [] = {     0x11, 0xff, 0x0d, 0x3c,
    0x00, 0x00, 0xFF, 0xFF, 
    0xFF, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
  };

  send_data(all, devh, 0);
  send_data(commit, devh, 0);
}


//_________________ WHITE WHEN CLOSE DEVICE_______________

void white_color_close(libusb_device_handle *devh)
{
  unsigned char commit [] = {	0x11, 0xFF, 0x3c, 0x5a, 
    0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x88,
    0x00, 0x00, 0x00, 0x00,
  };

  /*unsigned char wave [] =  {	0x11, 0xff, 0x0d, 0x3c, 
    0x00, 0x04, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 
    0x88, 0x02, 0x64, 0x02, 
    0x00, 0x00, 0x00, 0x00 
  };
*/
  unsigned char all [] = {     0x11, 0xff, 0x0d, 0x3c,
    0x00, 0x00, 0xFF, 0xFF, 
    0xFF, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
  };

  //send_data(wave, devh , 0);
  //send_data(commit, devh, 0);
 // sleep(3);	
  //printf("after wave");
  send_data(all, devh , 0);
  send_data(commit, devh , 0);  
  //sleep(1);
}


//_____________ SEND DATA TO THE WIRE IN USB _______________

void send_data(unsigned char *data, libusb_device_handle *devh, int i)
{
    int rc = 0;	
    if(i == 0)
    {
      rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1, 
          data , 20, 0);
    }

    else
    {
      rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0212, 1, 
          data , 64, 0);
    }
  (void)rc;
}
