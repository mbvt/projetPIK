#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

//=========================================================================
// This program tests out the libusb functions.
//=========================================================================

//struct ==> Stor Info Scane (SIS)
struct SIS
{
	ssize_t iprod;
	unsigned char strdesc[256];
};

int main ()
{
	libusb_device                    **devList = NULL;
	libusb_device                    *devPtr = NULL;
	libusb_device_handle             *devHandle = NULL;

	struct libusb_device_descriptor  devDesc;
//	int nb_usb = 10;
//	struct SIS *ptr_SIS;

	unsigned char              strDesc[256];
	ssize_t                    numUsbDevs = 0;      // pre-initialized scalars
	ssize_t                    idx = 0;
	int                        retVal = 0;
   //========================================================================
   // test out the libusb functions
   //========================================================================

   printf ("*************************\n USB Experiment Program:\n*************************\n");
   retVal = libusb_init (NULL);

   //========================================================================
   // Get the list of USB devices visible to the system.
   //========================================================================

   numUsbDevs = libusb_get_device_list (NULL, &devList);

   //========================================================================
   // Loop through the list, looking for the device with the required values
   // for Manufacturer ("RockwellCollins") and Product ("TACDIS").
   //========================================================================

   while (idx < numUsbDevs)
   {
      printf ("\n[%zd]\n", idx+1);

      //=====================================================================
      // Get next device pointer out of the list, use it to open the device.
      //=====================================================================

      devPtr = devList[idx];
      retVal = libusb_open (devPtr, &devHandle);
      if (retVal != LIBUSB_SUCCESS)
         break;

      //=====================================================================
      // Get the device descriptor for this device.
      //=====================================================================

      retVal = libusb_get_device_descriptor (devPtr, &devDesc);
      if (retVal != LIBUSB_SUCCESS)
         break;

      //=====================================================================
      // Get the string associated with iManufacturer index.
      //=====================================================================

      printf ("   iManufacturer = %d\n", devDesc.iManufacturer);
      if (devDesc.iManufacturer > 0)
      {
         retVal = libusb_get_string_descriptor_ascii
                  (devHandle, devDesc.iManufacturer, strDesc, 256);
         if (retVal < 0)
            break;

         printf ("   string = %s\n",  strDesc);
      }

      //========================================================================
      // Get string associated with iProduct index.
      //========================================================================

      printf ("   iProduct = %d\n", devDesc.iProduct);
      if (devDesc.iProduct > 0)
      {
         retVal = libusb_get_string_descriptor_ascii
                  (devHandle, devDesc.iProduct, strDesc, 256);
         if (retVal < 0)
            break;

         printf ("   string = %s\n", strDesc);
      }

      //==================================================================
      // Get string associated with iSerialNumber index.
      //==================================================================

      printf ("   iSerialNumber = %d\n", devDesc.iSerialNumber);
      if (devDesc.iSerialNumber > 0)
      {
         retVal = libusb_get_string_descriptor_ascii
                  (devHandle, devDesc.iSerialNumber, strDesc, 256);
         if (retVal < 0)
            break;

         printf ("   string = %s\n", strDesc);
      }

      //========================================================================
      // Close and try next one.
      //========================================================================

      libusb_close (devHandle);
      devHandle = NULL;
      idx++;
   }  // end of while loop

   if (devHandle != NULL)
   {
      //========================================================================
      // Close device if left open due to break out of loop on error.
      //========================================================================

      libusb_close (devHandle);
   }   

   libusb_exit (NULL);

   printf ("\n*************************\n        Done\n*************************\n");
   return 0;
}

//==========================================
// EOF
//==========================================
