#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <inttypes.h>
#include <libusb-1.0/libusb.h>


static struct libusb_device_handle *devh = NULL;

struct struct_key   {
  uint16_t   num_w;
  uint16_t   num_r;
  char       array_nom[100];
  int        number_key;
  int        bit;
  int        groupe;
};

struct struct_write {
  uint16_t speed;
  uint16_t red;
  uint16_t green;
  uint16_t blue;
  uint16_t key;
  libusb_device_handle *devh;
};


//____________________ R E A D ______________________________________
struct struct_key  read_chars(unsigned char * data, int size, struct struct_key key)
{
  int actual_length = 0;
  int rc;

  for (int i=0;i<size;data[i++]=0);;

  rc = libusb_bulk_transfer(devh, 0x81, data, 8, &actual_length,
      10);
  if(actual_length > 0)
  {
    for(int i = 0; i < actual_length; i++)
    {
      if(data[i] != 0)
      {
        //key.code_key = data[i];
        //key.position_bit = i;
        //fprintf(stdout, " code_key      : 0x%02x \n", key.code_key);
        //fprintf(stdout, " position_bit  : %d \n\n", key.position_bit);
      }
    }
    fprintf(stdout, "----------------------  \n");

  }
  (void)rc;
  return key;
}

//________________________C O L O R__________________________
void keybordcolor(struct struct_write *str)
{
  int rc = 0;
  /*
  fprintf(stdout, "\n\n=======color recive =====\n"); 

  fprintf(stdout,"key : %02x \n", str->key);
  fprintf(stdout,"red : %02x \n", str->red);
  fprintf(stdout,"green : %02x \n", str->green);
  fprintf(stdout,"blue : %02x \n", str->blue);
  fprintf(stdout,"speed : %02x \n", str->speed);
*/
  uint16_t speed = str->speed;
  uint16_t red = str->red;
  uint16_t green = str->green;
  uint16_t blue = str->blue;       
  uint16_t key = str->key;
  libusb_device_handle *devh = str->devh; 

  unsigned char data_commit [] = { 0x11, 0xff, 0x0c, 0x5a, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  unsigned char data1 [] = { 0x12, 0xff, 0x0c , 0x3a,
    0x00, speed, 0x00, 0x0e, 
    key, red, green, blue, 
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


  rc = libusb_control_transfer(devh, 0x21, 0X09, 0x0212, 1, 
      data1, sizeof(data1), 10); 

  rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1, 
      data_commit, sizeof(data_commit), 10); 
  (void)rc;
}

//_____________________ U S B  -  I N I T ________________________
libusb_device_handle* USB_Init()
{
  libusb_device_handle  *devh = NULL;
  uint16_t  PRODUCT_ID = 0xc330;
  uint16_t VENDOR_ID = 0x046d;
  int res = 0;

  res = libusb_init(NULL);
  if(res < 0)
    fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(res));
  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  for (int if_num = 0; if_num < 2; if_num++) 
  {
    if (libusb_kernel_driver_active(devh, if_num)) 
      libusb_detach_kernel_driver(devh, if_num);
    res = libusb_claim_interface(devh, if_num);
  }
  return devh;
}

//_____________________ U S B  -  C L O S E  ________________________
void USB_Close(libusb_device_handle *devh)
{
  libusb_release_interface(devh, 0);
  libusb_release_interface(devh, 1);

  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);

  if(devh)
    libusb_close(devh);
  libusb_exit(NULL);
}


int write_to_keybord (libusb_device_handle *devh)
{
  struct struct_write *str = malloc (sizeof (struct struct_write ));  
  uint16_t variable_local = 0x00;
  int rc = 0;
  
  fprintf(stdout,"\n--------------\n Key :");
  rc = scanf("%04x" , &variable_local);
  fprintf(stdout,"\n Red :");
  rc = scanf("%04x" , &str->red);
  fprintf(stdout,"\n Green :");
  rc = scanf("%04x" , &str->green);
  fprintf(stdout,"\n Blue :");
  rc = scanf("%04x" , &str->blue);
  fprintf(stdout,"\n Blue :");
  fprintf(stdout,"\n");
  str->speed = 0x01;
  str->devh = devh;
  str->key = variable_local;
  
  keybordcolor(str);
  
  free(str);    
  (void)rc;
  
  if(str->key == 0x29)
    return 1;

  return 0;
}


//_______________ R E A D - T O - K E Y B O R D _________________
int   read_to_keybord(libusb_device_handle *devh)
{
  unsigned char data_read[64];
  int size = 64;
  int rc = 0;
  int actual_length = 0;

  for ( int i=0 ; i < size ; data_read[i++] = 0 );; 

  rc = libusb_bulk_transfer(devh, 0x81, data_read, 8, &actual_length, 10);
  if(actual_length > 0)
  {
    for(int i = 0; i < actual_length; i ++)
    {
      if(data_read[i] != 0) 
      {
        fprintf(stdout, "------\nkey code : %02x \n------\n", data_read[i]);
        if(data_read[i] == 0x29)
          return 1;
      }
    }
  }
  (void)rc;
  return 0;
}

//----------------------- M A I N ---------------------------
int main()
{
  //INIT LIBUSB
  libusb_device_handle  *devh = NULL;
  devh = USB_Init();
  //-----------------------------------------|
  // TEST WITH WRITE 
  printf("begin test write : choose key to color");
  int res = 0;
  while(res == 0)
  {
    res = write_to_keybord(devh);
  }
  //-----------------------------------------|
  //TEST_TO_READ
  res = 0;
  printf("\nbegin test read : choose key to color\n");
  while(res == 0)
  {
    res = read_to_keybord(devh);
  }
  (void)res;
  //-------------------------------------------|
  //END TEST ==> CLOSE LIBUSB
  USB_Close(devh);
  return 0;
} 
//------------------- E N D _ M A I N -----------------------
