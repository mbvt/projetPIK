#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <libusb-1.0/libusb.h>

/* You may want to change the VENDOR_ID and PRODUCT_ID
 * depending on your device.
 */
#define VENDOR_ID       0x046d   // Arduino LLC
#define PRODUCT_ID      0xc330   // Arduino Leonardo

#define ACM_CTRL_DTR    0x01
#define ACM_CTRL_RTS    0x02

/* We use a global variable to keep the device handle
 */
static struct libusb_device_handle *devh = NULL;

/* The Endpoint address are hard coded. You should use lsusb -v to find
 * the values corresponding to your device.
 */
static int ep_in_addr  = 0x81;
static int ep_out_addr = 0x02;

//----------------------------------------------------------
void write_char(unsigned char c)
{
  /* To send a char to the device simply initiate a bulk_transfer to the
   * Endpoint with address ep_out_addr.
   */
  int actual_length;
  if (libusb_bulk_transfer(devh, ep_out_addr, &c, 8,
        &actual_length, 0) < 0) {
    fprintf(stderr, "Error while sending char\n");
  }
}

//-------------------------------------------------------------
void read_chars(unsigned char * data, int size)
{
  int actual_length = 0;
  int rc;
for (int i=0;i<size;data[i++]=0);;
  rc = libusb_bulk_transfer(devh, ep_in_addr, data, 32, &actual_length,
      500);
  if(actual_length >0)
  {
    for(int i = 0; i < actual_length +2; i++)
    {
      fprintf(stdout, " data read :   %d\n", (int)data[i]);
    }
    fprintf(stdout, "size bytes transferred (%d)\n", actual_length);
  }
  else
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
}

void keybordcolor()
{
  int rc = 0;
  unsigned char data1 [] = { 0x11, 0xff, 0x0d, 0x3c,
                             0x00, 0x01, 0xFF, 0xFF, 
                             0xFF, 0x00, 0x00, 0x00, 
                             0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00,
              };

  unsigned char data2 [] = { 0x11, 0xff, 0x0d, 0x3c,
                        0x00, 0x04, 0xFF, 0xFF, 
                        0xFF, 0x40, 0x10, 0x00, 
                        0x64, 0x00, 0x00, 0x00, 
                        0x00 , 0x00, 0x00 , 0x00,
              };

  unsigned char commit [] = { 0x11, 0xff, 0x3c, 0x5a,
                        0x04 , 0x00 , 0x00 , 0x00, 
                        0x00 , 0x00 , 0x00 , 0x88, 
                        0x01 , 0x64 , 0x00 , 0x00,
                        0x00 , 0x00 , 0x00 , 0x00,
              };

rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1, 
  data1, sizeof(data2), 2000); 
  printf(" rc = %d \n", rc);
  sleep(5); 
 
  rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1,data1,
  sizeof(data2),2000); 
  printf(" rc = %d \n", rc);
  sleep(5);

  rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0212, 1,commit,
  sizeof(commit),2000); 
  printf(" rc = %d \n", rc);
  sleep(5);
}

//----------------------- M A I N ---------------------------
int main()
{
  int rc;

  /* Initialize libusb
   */
  rc = libusb_init(NULL);
  if (rc < 0) {
    fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(rc));
    exit(1);
  }

  /* Set debugging output to max level.
   */
  libusb_set_debug(NULL, 3);

  /* Look for a specific device and open it.
   */
  devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
  if (!devh) {
    fprintf(stderr, "Error finding USB device\n");
    goto out;
  }

  for (int if_num = 0; if_num < 2; if_num++) {
    if (libusb_kernel_driver_active(devh, if_num)) {
      libusb_detach_kernel_driver(devh, if_num);
    }
    rc = libusb_claim_interface(devh, if_num);
    if (rc < 0) {
      fprintf(stderr, "Error claiming interface: %s\n",
          libusb_error_name(rc));
      goto out;
    }
  }

  keybordcolor();
  
  /* unsigned char data_status [32];

     rc = libusb_control_transfer(devh, 0x80, 0x06 , 0x00, 0,
     data_status, sizeof(data_status)  , 0);

     if (rc < 0) {
     fprintf(stderr, "Error during control transfer: %s\n",
     libusb_error_name(rc));
     }

     else
     {
     for ( unsigned int i = 0; i < sizeof ( data_status); i++)
     {
     printf(" %d \n", (char)data_status[i]);
     }
     }


  // - set line encoding: here 9600 8N1
  // 9600 = 0x2580 ~> 0x80, 0x25 in little endian
  //
  unsigned char encoding[] = { 0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08 };

  rc = libusb_control_transfer(devh, 0x80, 0x01, 0, 0, encoding,
  sizeof(encoding), 0);
  if (rc < 0) {
  fprintf(stderr, "Error during control transfer: %s\n",
  libusb_error_name(rc));
  }


  // We can now start sending or receiving data to the device
   */
  unsigned char data_read[65];
  int i = 40;
  while(i < 20)
  {
    read_chars(data_read, 64);
    sleep(1);
    i++;
  }

  libusb_release_interface(devh, 0);
  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);
out:
  if (devh)
    libusb_close(devh);
  libusb_exit(NULL);
  return 1;
} 
