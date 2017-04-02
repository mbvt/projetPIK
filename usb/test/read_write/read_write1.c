#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

//---------------------------------------------------------------------------//
// Values for bmRequestType in the Setup transaction's Data packet.
static const int CONTROL_REQUEST_TYPE_IN =  LIBUSB_ENDPOINT_IN | 
                                            LIBUSB_REQUEST_TYPE_CLASS | 
                                            LIBUSB_RECIPIENT_INTERFACE;

static const int CONTROL_REQUEST_TYPE_OUT = LIBUSB_ENDPOINT_OUT | 
                                            LIBUSB_REQUEST_TYPE_CLASS | 
                                            LIBUSB_RECIPIENT_INTERFACE;

//---------------------------------------------------------------------------//
// From the HID spec:
static const int                            HID_GET_REPORT = 0x01;//clear_feart
static const int                            HID_SET_REPORT = 0x09;//set_config
static const int                            HID_REPORT_TYPE_INPUT = 0x01;
static const int                            HID_REPORT_TYPE_OUTPUT = 0x02;
static const int                            HID_REPORT_TYPE_FEATURE = 0x03;

//---------------------------------------------------------------------------//
// With firmware support, transfers can be > the endpoint's max packet size.
static const int                            MAX_CONTROL_IN_TRANSFER_SIZE = 8;
static const int                            MAX_CONTROL_OUT_TRANSFER_SIZE = 8;
static const int                            INTERFACE_NUMBER = 0;
static const int                            TIMEOUT_MS = 5000;

//exchange_input_and_output_reports_via_interrupt_transfers   //code 1
//exchange_feature_reports_via_control_transfers              //code 2


int exchange_input_and_output_reports_via_interrupt_transfers(
    libusb_device_handle *devh);

int exchange_feature_reports_via_control_transfers(
    libusb_device_handle *devh,
    struct libusb_control_setup *Setup); 

int exchange_input_and_output_reports_via_control_transfers(
    libusb_device_handle *devh);
/*
int fonct_found_dev(struct libusb_device_descriptor devDesc, 
                    uint16_t productId, uint16_t ventorId)
{
  libusb_device                    **devList = NULL;
  libusb_device                    *devPtr = NULL;
  libusb_device_handle             *devHandle = NULL;
  struct libusb_control_setup  Setup;
  int 			   device_found =0;
  ssize_t                    idx = 0;
  ssize_t                    numUsbDevs = 0;
  int                        retVal;
  numUsbDevs = libusb_get_device_list(NULL, &devList);
  while((devDesc.idVendor != ventorId) && (devDesc.idProduct != productId) && (idx < numUsbDevs))
  {
    devPtr = devList[idx];
    retVal = libusb_open (devPtr, &devHandle);
    retVal = libusb_get_device_descriptor (devPtr, &devDesc);
    idx ++;
    if((devDesc.idVendor == ventorId) && (devDesc.idProduct == productId))
    {
      device_found = 1;
      break;
    }
  }
  //------- TEMPORAIRE --------//
  printf(" bmRequestType = 0x%02x\n",Setup.bmRequestType);
  printf(" bRequest = 0x%02x\n",Setup.bRequest);
  printf(" wValue = 0x%04x\n",Setup.wValue);
  printf(" wIndex = 0x%04x\n",Setup.wIndex);
  printf(" wLength = 0x%02x\n",Setup.wLength);
  //---------------------------//
  (void)retVal;
  return device_found;
} 
*/
  //-----------------------------------------------------------------//
  //                              MAIN                               //
  // ----------------------------------------------------------------//
int main ()
{
  // Change these as needed to match idVendor and idProduct 
  // in your device's device descriptor.

  //static const int        VENDOR_ID = 0x0c45;
  //static const int        PRODUCT_ID = 0x8060;
  
  // -----  CLAVIER THOMAS -------
  //static const int        VENDOR_ID = 0x04d9;
  //static const int        PRODUCT_ID = 0x0024;

// -----  CLAVIER LOGITEC --------
  static const int          VENDOR_ID = 0x046d;
  static const int          PRODUCT_ID = 0xc330;
  
  struct                  libusb_device_handle *devh = NULL;
  int                     result = 0;
  int                     kernelDriverDetached = 0;
    
    result = libusb_init (NULL);

  struct libusb_control_setup       *Setup;
  struct libusb_transfer            *transfer;                                      
  transfer = libusb_alloc_transfer(60);
  transfer->buffer = malloc( 128 * sizeof (unsigned char));

  if (result >= 0)
  {
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    if (devh != NULL)
    {
      // The HID has been detected.
      // Detach the hidusb driver from the HID to enable using libusb.
      if(libusb_kernel_driver_active(devh, 0))
      {
        result = libusb_detach_kernel_driver(devh, INTERFACE_NUMBER);
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
    }
  }
    
      Setup = libusb_control_transfer_get_setup(transfer); 
   if(result >=0)
   {
    printf("reslut > 0\n");
     // Send and receive data.
     //exchange_input_and_output_reports_via_interrupt_transfers(devh);
     exchange_feature_reports_via_control_transfers(devh, Setup);
    //exchange_input_and_output_reports_via_control_transfers(devh, Setup);
   }
    // Finished using the device.
  printf("ici \n");
  if(kernelDriverDetached)
  {
    printf("ici2\n");
    result = libusb_attach_kernel_driver(devh, 0);
  }
  libusb_release_interface(devh, 0);
  libusb_close(devh);
  libusb_exit(NULL);
  return 0;
}
//----------------------  FIN MAIN  ---------------------//




       //-----------------------------------------------------//
      //                       CODE    1                      //
     //-------------------------------------------------------//

// Uses control transfers to write a Feature report to the HID
// and receive a Feature report from the HID.
// Returns - zero on success, libusb error code on failure.
int exchange_input_and_output_reports_via_interrupt_transfers(
    libusb_device_handle *devh)
{

  // Assumes interrupt endpoint 2 IN and OUT:

  //static const int INTERRUPT_IN_ENDPOINT = 0x80;
  //static const int INTERRUPT_OUT_ENDPOINT = 0x00;

  // With firmware support, transfers can be > the endpoint's max packet size.

  static const int MAX_INTERRUPT_IN_TRANSFER_SIZE = 8;
  static const int MAX_INTERRUPT_OUT_TRANSFER_SIZE = 8;

  int bytes_transferred;
  int i = 0;
  int result = 0;;

  unsigned char data_in[MAX_INTERRUPT_IN_TRANSFER_SIZE];
  unsigned char data_out[MAX_INTERRUPT_OUT_TRANSFER_SIZE];

  // Store data in a buffer for sending.

  for (i=0;i < MAX_INTERRUPT_OUT_TRANSFER_SIZE; i++)
  {
    data_out[i]=0x00;
  }

  //- - - WRITE - - - data to the device.
  result = libusb_interrupt_transfer(
      devh,
      LIBUSB_ENDPOINT_OUT ,
      data_out,
      sizeof(data_out),
      &bytes_transferred,
      TIMEOUT_MS);

  if (result >= 0)
  {
    printf("Data sent via interrupt transfer:\n");
    for(i = 0; i < bytes_transferred; i++)
    {
      printf("%02x ",data_out[i]);
    }
    printf("\n");

    // - - - READ - - -  data from the device.
    result = libusb_interrupt_transfer(
        devh,
        LIBUSB_ENDPOINT_IN,
        data_in,
        sizeof(data_in),
        &bytes_transferred,
        TIMEOUT_MS);

    if (result >= 0)
    {
      if (bytes_transferred > 0)
      {
          printf("Data received via interrupt transfer:\n");
            for(i = 0; i < bytes_transferred; i++)
            {
              printf("%02x ",data_in[i]);
            }
          printf("\n");
      }
      else
      {
        fprintf(stderr,"No data received in interrupt transfer(%d)\n",result);
        return -1;
      }
    }
    else
    {
      fprintf(stderr,"Error receiving data via interrupt transfer %d\n",result);
      return result;
    }
  }
  else
  {
    fprintf(stderr, "Error sending data via interrupt transfer %d\n",result);
    return result;
  }
  return 0;
}

          //-----------------------------------------------------//
         //                       CODE    2                      //
        //-------------------------------------------------------//
    
int exchange_feature_reports_via_control_transfers(libusb_device_handle *devh,
struct libusb_control_setup *Setup)
{
  int               bytes_received;
  int               bytes_sent;
  unsigned char     data_in[MAX_CONTROL_IN_TRANSFER_SIZE];
  unsigned char     data_out[MAX_CONTROL_OUT_TRANSFER_SIZE];	
  int               i = 0;
  int               result = 0;

  // Store example data in the output buffer for sending.
  // This example uses binary data.
  for (i=0;i < MAX_CONTROL_OUT_TRANSFER_SIZE; i++)
  {
    data_out[i]=0x00+i;
  }

  // Send data to the device.
  bytes_sent = libusb_control_transfer(
      devh,
      CONTROL_REQUEST_TYPE_OUT ,
      HID_SET_REPORT,
      (HID_REPORT_TYPE_FEATURE<<8)|0x00,
      INTERFACE_NUMBER,
      data_out,
      sizeof(data_out),
      TIMEOUT_MS);


  //------- TEMPORAIRE --------//
  printf(" bmRequestType = 0x%02x\n", Setup->bmRequestType);
  printf(" bRequest = 0x%02x\n", Setup->bRequest);
  printf(" wValue = 0x%04x\n", Setup->wValue);
  printf(" wIndex = 0x%04x\n", Setup->wIndex);
  printf(" wLength = 0x%02x\n", Setup->wLength);
  //---------------------------//   
/*
bytes_sent = libusb_control_transfer(
      devh,
      Setup->bmRequestType,
      Setup->bRequest,
      Setup->wValue,
      Setup->wIndex,
      data_out,
      8,
      2000);
  */
  if (bytes_sent >= 0)
  {
    printf("Feature report data sent:\n");
    for(i = 0; i < bytes_sent; i++)
    {
      printf("%02x ",data_out[i]);
    }
    printf("\n");

    
    // Request data from the device.
    bytes_received = libusb_control_transfer(
        devh,
        CONTROL_REQUEST_TYPE_IN ,
        HID_GET_REPORT,
        (HID_REPORT_TYPE_FEATURE<<8)|0x00,
        INTERFACE_NUMBER,
        data_in,
        MAX_CONTROL_IN_TRANSFER_SIZE,
        TIMEOUT_MS);
    
    /*  
    bytes_received = libusb_control_transfer(
              devh,
              0xf8,
              0xdb,
              0x16b0,
              0x7fb0,
              data_in,  
              8,
              2000); 
*/
    if (bytes_received >= 0)
    {
      printf("Feature report data received:\n");
      for(i = 0; i < bytes_received; i++)
      {
        printf("%02x ",data_in[i]);
      }
      printf("\n");
    }
    else
    {
      fprintf(stderr, "Error receiving Feature report %d\n", result);
      return result;
    }
  }
  else
  {
    fprintf(stderr, "Error sending Feature report %d\n", result);
    return result;
  }
  return 0;
}



          //-----------------------------------------------------//
         //                       CODE    3                      //
        //-------------------------------------------------------//
// Uses control transfers to write an Output report to the HID
// and receive an Input report from the HID.
// Returns - zero on success, libusb error code on failure.
int exchange_input_and_output_reports_via_control_transfers(
    libusb_device_handle *devh)
{
  int               bytes_received;
  int               bytes_sent;
  unsigned char     data_in[MAX_CONTROL_IN_TRANSFER_SIZE];
  unsigned char     data_out[MAX_CONTROL_OUT_TRANSFER_SIZE];	
  int               i = 0;
  int               result = 0;

  // Store example data in the output buffer for sending.
  // This example uses binary data.

  for (i=0;i < MAX_CONTROL_OUT_TRANSFER_SIZE; i++)
  {
    data_out[i]=0x00;
  }

  // Send data to the device.

  bytes_sent = libusb_control_transfer(
      devh,
      CONTROL_REQUEST_TYPE_OUT ,
      HID_SET_REPORT,
      (HID_REPORT_TYPE_OUTPUT<<8)|0x00,
      INTERFACE_NUMBER,
      data_out,
      sizeof(data_out),
      TIMEOUT_MS);

  if (bytes_sent >= 0)
  {
    printf("Output report data sent:\n");
    for(i = 0; i < bytes_sent; i++)
    {
      printf("%02x ",data_out[i]);
    }
    printf("\n");

    // Request data from the device.

    bytes_received = libusb_control_transfer(
        devh,
        CONTROL_REQUEST_TYPE_IN ,
        HID_GET_REPORT,
        (HID_REPORT_TYPE_INPUT<<8)|0x00,
        INTERFACE_NUMBER,
        data_in,
        MAX_CONTROL_IN_TRANSFER_SIZE,
        TIMEOUT_MS);

    if (bytes_received >= 0)
    {
      printf("Input report data received:\n");
      for(i = 0; i < bytes_received; i++)
      {
        printf("%02x ",data_in[i]);
      }
      printf("\n");
    }
    else
    {
      fprintf(stderr, "Error receiving Input report %d\n", result);
      return result;
    }
  }
  else
  {
    fprintf(stderr, "Error sending Input report %d\n", result);
    return result;
  }
  return 0;
}
// Use interrupt transfers to to write data to the 
// device and receive data from the device.

// Returns - zero on success, libusb error code on failure.
