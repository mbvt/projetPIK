#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>


/*void init_tranfer(struct libusb_transfer *transfer,struct libusb_control_setup  
 *Setup,  libusb_device_handle *devHandle)                       
 {                                                                               
 unsigned char                 buffer[10];                   
 int                           completed = 0;                                      
 libusb_transfer_cb_fn         &callback;

 libusb_fill_control_setup(buffer,                                             
 Setup->bmRequestType,                               
 Setup->bRequest,                                    
 Setup->wValue,                                      
 Setup->wIndex,                                      
 Setup->wLength);                                    


 libusb_fill_control_transfer(transfer, devHandle, buffer, callback, &completed,
 1000);

 libusb_submit_transfer(transfer);                                             
 }                                                   
 */
//---------------------------------------------------------------------------//

int main ()
{
//  libusb_device                    **devList = NULL;
  //libusb_device                    *devPtr = NULL;
  libusb_device_handle             *devHandle = NULL;

  struct                            libusb_device_descriptor   devDesc;
  static const int                  INTERFACE_NUMBER = 0;
  int			                          result = 0;
  int                               device_ready = 0;
  int                               kernelDriverDetached = 0;
  //                Clavier
  //---------------------------------------------------------------------//
  //uint16_t		   productId = 0x8060;  
  //uint16_t		   ventorId = 0x0c45;
  //---------------------------------------------------------------------//

  //                Souris
  //---------------------------------------------------------------------//     
  //uint16_t       productId = 0xa086;                                            
  //uint16_t       ventorId = 0x04d9;                                             
  //---------------------------------------------------------------------// 

  result = libusb_init (NULL);

  struct libusb_control_setup       *Setup;
  struct libusb_transfer            *transfer;                                      
  transfer = libusb_alloc_transfer(60);
  transfer->buffer = malloc( 128 * sizeof (unsigned char));

  if (result >= 0)
  {
    devHandle = libusb_open_device_with_vid_pid(NULL, ventorId, productId);

    if (devHandle != NULL)
    {
      // The HID has been detected.
      // Detach the hidusb driver from the HID to enable using libusb.
      if(libusb_kernel_driver_active(devHandle, 0))
      {
        result = libusb_detach_kernel_driver(devHandle, INTERFACE_NUMBER);
        if(result == 0)
        {
          kernelDriverDetached = 1;
        }
        else
        {
          printf("erro detaching kernel driver\n");
          return 1;
        }
      }

      device_ready = 1;
      Setup = libusb_control_transfer_get_setup(transfer); 
    }
  }
int num_press_key = 0;
  for(; num_press_key < 5;  )
  {
      reslut = libusb_bulk_transfer(devHandle, endpoint,
  }
  //init_tranfer(transfer, Setup, devHandle);
  if(kernelDriverDetached)
  {
    result =  libusb_attach_kernel_driver(devHandle, 0);
  }

  (void)result;
  (void)device_ready;
  libusb_close (devHandle);
  devHandle = NULL;
  libusb_exit (NULL);
  return 0;

}
