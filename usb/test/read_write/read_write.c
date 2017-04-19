#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <libusb-1.0/libusb.h>

#define VENDOR_ID       0x046d   
#define PRODUCT_ID      0xc330   

#define ACM_CTRL_DTR    0x01
#define ACM_CTRL_RTS    0x02

static struct libusb_device_handle *devh = NULL;

struct struct_key {
                  uint16_t   code_key;        //code en HEXA
                  int        number_key;      //Nb touche appuier en meme temps
                  int        num;             // Numero dans le tableau  
                                              // de convertion // HEXA / touches
                  int        position_bit;
                  };

struct struct_key convert_read(struct struct_key key)
{
    
}

struct struct_key Convert_write(struct struct_key key)

//-------------------------------------------------------------
struct struct_key  read_chars(unsigned char * data, int size, struct struct_key key)
{
  int actual_length = 0;
  int rc;
  
  //uint16_t struct_key.code_key;
  
  for (int i=0;i<size;data[i++]=0);;

  rc = libusb_bulk_transfer(devh, 0x81, data, 8, &actual_length,
      10);
  if(actual_length > 0)
  {
        for(int i = 0; i < actual_length; i++)
        {
            if(data[i] != 0)
            {
                key.code_key = data[i];
                key.position_bit = i;
                fprintf(stdout, " code_key      : 0x%02x \n", key.code_key);
                fprintf(stdout, " position_bit  : %d \n\n", key.position_bit);
            }
        }
        fprintf(stdout, "----------------------  \n");
        
  }

 /*  else
  {
   printf("no bytes recive \n ");
    switch (rc) 
    {
      case LIBUSB_ERROR_TIMEOUT:
        fprintf(stderr, " LIBUSB_ERROR_TIMEOUT !!! \n");
        break;

      case LIBUSB_ERROR_PIPE:
        fprintf(stderr, " LIBUSB_ERROR_PIPE !!! \n");
        break;
      case LIBUSB_ERROR_OVERFLOW:
        fprintf(stderr, " LIBUSB_ERROR_OVERFLOW !!! \n");
        break;
      default:
        fprintf(stderr, " LIBUSB_ERROR OTHER  !!! \n");
    }
  }
  */
  (void)rc;
  return key;
}

void keybordcolor()
{
  int rc = 0;
  // 0x11 0xff 0x0d 0x3c  
  // 0x00 Touche Red Green Bleu 

  uint16_t speed = 0x01;
  uint16_t red = 0x00;        // RED
  uint16_t green = 0xff;       // GREEN
  uint16_t blue = 0x00;       // BLUE
  uint16_t key = 0x39;
  
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
  printf("rc = %d \n", rc );

  rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1, 
      data_commit, sizeof(data_commit), 10); 
  printf("rc = %d \n", rc );
}

//----------------------- M A I N ---------------------------
int main()
{
  int rc;

  /* Initialize libusb
   */
  rc = libusb_init(NULL);
  if (rc < 0) {
//    fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
    exit(1);
  }

  //libusb_set_debug(NULL, 3);

  /* Look for a specific device and open it.
   */
  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  if (!devh) {
  //  fprintf(stderr, "Error finding USB device\n");
    //goto out;
  }
  
     for (int if_num = 0; if_num < 2; if_num++) 
     {
        if (libusb_kernel_driver_active(devh, if_num)) 
              libusb_detach_kernel_driver(devh, if_num);
        rc = libusb_claim_interface(devh, if_num);
        if (rc < 0)
        {
    //        fprintf(stderr, "Error claiming interface: %s\n",
     //       libusb_error_name(rc));
    //        goto out;
        }
     }
   
//   keybordcolor();



  unsigned char data_read[1024];
  struct struct_key key;
  while(1)
  {
    key = read_chars(data_read, 64, key);
    //sleep(0.1);
}

  libusb_release_interface(devh, 0);
  libusb_release_interface(devh, 1);

  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);

  if (devh)
    libusb_close(devh);
  libusb_exit(NULL);
  return 1;
} 
