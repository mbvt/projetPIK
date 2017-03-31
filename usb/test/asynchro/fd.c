#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

void save_info_device(struct libusb_device_descriptor
    devDesc, libusb_device_handle *devHandle,struct libusb_control_setup *Setup)
{
  unsigned char              strDesc[256];
  int retVal = 0;

  FILE* file = NULL;
  file = fopen("result_desciption_clavier.txt","wr");
  retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
  fprintf (file, "	|------------------------------------------------------------|\n");
  fprintf(file,"	|	                                                     	     |\n");
  fprintf(file,"	|			                  KEYBORD - USB            	  		     |\n");
  fprintf(file,"	|	                        			                             |\n");
  fprintf(file,"	|____________________________________________________________|\n\n");

  //=====================================================================
  //                              bLength.
  //=====================================================================
  fprintf (file,"bLength, Size of this descriptor = 0x%02x\n", devDesc.bLength);
  if (devDesc.bLength > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle,devDesc.bLength, strDesc, 256);
    fprintf(file, "%s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                           bDescriptorType
  //=====================================================================
  fprintf (file,"bDescriptorType, Descriptor type = 0x%02x\n", devDesc.bDescriptorType );
  if (devDesc.bDescriptorType > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDescriptorType, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                              bcdUSB 
  //=====================================================================
  fprintf (file,"bcdUSB, USB specification release number in binary-coded decimal = 0x%04x\n", devDesc.bcdUSB );
  if (devDesc.bcdUSB > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdUSB, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          bDeviceClass 
  //=====================================================================
  fprintf (file,"bDeviceClass, USB-IF class code for the device = 0x%02x\n", devDesc.bDeviceClass);
  if (devDesc.bDeviceClass > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceClass, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          bDeviceSubClass 
  //=====================================================================
  fprintf (file,"bDeviceSubClass, qualified by the bDeviceClass value  = 0x%02x\n", devDesc.bDeviceSubClass);
  if (devDesc.bDeviceSubClass > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceSubClass, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          bDeviceProtocol 
  //=====================================================================
  fprintf (file,"bDeviceProtocol,qualified by the bDeviceClass and bDeviceSubClass values  = 0x%02x\n", devDesc.bDeviceProtocol);
  if (devDesc.bDeviceProtocol > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceProtocol, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          bMaxPacketSize0 
  //=====================================================================
  fprintf (file,"bMaxPacketSize0, Maximum packet size for endpoint 0  = 0x%02x\n", devDesc.bMaxPacketSize0);
  if (devDesc.bMaxPacketSize0 > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bMaxPacketSize0, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          idVendor 
  //=====================================================================
  fprintf (file,"idVendor, USB-IF vendor ID = 0x%04x\n", devDesc.idVendor);
  if (devDesc.idVendor > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idVendor, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          idProduct 
  //=====================================================================
  fprintf (file,"idProduct, USB-IF product ID.  = 0x%04x\n", devDesc.idProduct);
  if (devDesc.idProduct > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idProduct, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          bcdDevice 
  //=====================================================================
  fprintf (file,"bcdDevice, USB-IF product ID.  = 0x%04x\n", devDesc.bcdDevice);
  if (devDesc.bcdDevice > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdDevice, strDesc, 256);
    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //=====================================================================
  //                          iManufacturer
  //=====================================================================
  fprintf (file,"iManufacturer, string descriptor describing manufacturer = 0x%02x\n", devDesc.iManufacturer);
  if (devDesc.iManufacturer > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iManufacturer, strDesc, 256);

    fprintf(file, " %s\n",  strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //========================================================================
  //                              iProduct
  //========================================================================

  fprintf (file, "iProduct, Index of string descriptor describing product  = 0x%02x\n", devDesc.iProduct);
  if (devDesc.iProduct > 0)
  {
    retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
    fprintf (file, "%s\n", strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //==================================================================
  //                            iSerialNumber
  //==================================================================

  fprintf (file,"iSerialNumber, string descriptor containing device serial number = 0x%02x\n", devDesc.iSerialNumber);
  if (devDesc.iSerialNumber > 0)
  {
    retVal = libusb_get_string_descriptor_ascii
      (devHandle, devDesc.iSerialNumber, strDesc, 256);
    fprintf (file,"%s\n", strDesc);
  }
  fprintf(file,"---------------------------------------------------------------\n");
  //==================================================================
  //                            bNumConfigurations
  //==================================================================

  fprintf (file,"bNumConfigurations, Number of possible configurations = 0x%02x\n", devDesc.bNumConfigurations);
  if (devDesc.bNumConfigurations> 0)
  {
    retVal = libusb_get_string_descriptor_ascii
      (devHandle, devDesc.bNumConfigurations, strDesc, 256);
    fprintf (file,"%s\n", strDesc);
  }

  //==================================================================
  //                            All  Setup
  //==================================================================
  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file," bmRequestType = 0x%02x\n",Setup->bmRequestType);
  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file," bRequest = 0x%02x\n",Setup->bRequest);
  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file," wValue = 0x%04x\n",Setup->wValue);
  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file," wIndex = 0x%04x\n",Setup->wIndex);
  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file," wLength = 0x%02x\n",Setup->wLength);


  fprintf(file,"---------------------------------------------------------------\n");
  fprintf(file,"			            	    { END PROGRAMME }	                      \n");
  fprintf(file,"---------------------------------------------------------------\n");
  (void)retVal;
  fclose(file);
}
//---------------------------------------------------------------------------//

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

//                Clavier                                                     
//---------------------------------------------------------------------//     
uint16_t       productId = 0xa086;                                          
uint16_t       ventorId = 0x04d9;                                           
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
      save_info_device(devDesc ,devHandle, Setup);          
    }
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
