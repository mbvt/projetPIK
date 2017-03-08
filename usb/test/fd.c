#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>
/*
   struct SIS
   {
   ssize_t iprod;
   unsigned char strdesc[256];
   };
 */
int main ()
{
	libusb_device                    **devList = NULL;
	libusb_device                    *devPtr = NULL;
	libusb_device_handle             *devHandle = NULL;

	struct libusb_device_descriptor  devDesc;
	//	int nb_usb = 10;
	//	array_desc = calloc(nb_usb, sizeof (struct SIS));
	//	struct SIS *ptr_SIS;

	unsigned char              strDesc[256];
	ssize_t                    idx = 0;
	ssize_t			   numUsbDevs = 0;
	int                        retVal = 0;

	FILE* file = NULL;
	file = fopen("result_desciption_clavier.txt","w");	

	retVal = libusb_init (NULL);
	numUsbDevs = libusb_get_device_list (NULL, &devList);

	devPtr = devList[idx];
	retVal = libusb_open (devPtr, &devHandle);

	retVal = libusb_get_device_descriptor (devPtr, &devDesc);

	//=====================================================================
	// Get the string associated with iManufacturer index.
	//=====================================================================

	fprintf (file,"iManufacturer = %d\n", devDesc.iManufacturer);
	if (devDesc.iManufacturer > 0)
	{
		retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iManufacturer, strDesc, 256);

		fprintf(file, "desc iManu ==> %s\n",  strDesc);
	}

	//========================================================================
	// Get string associated with iProduct index.
	//========================================================================

	fprintf (file, "iProduct = %d\n", devDesc.iProduct);
	if (devDesc.iProduct > 0)
	{
		retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);

		fprintf (file, "desc iProd ==> %s\n", strDesc);
	}

	//==================================================================
	// Get string associated with iSerialNumber index.
	//==================================================================

	fprintf (file,"iSerialNumber = %d\n", devDesc.iSerialNumber);
	if (devDesc.iSerialNumber > 0)
	{
		retVal = libusb_get_string_descriptor_ascii
			(devHandle, devDesc.iSerialNumber, strDesc, 256);
		fprintf (file,"desc iSerialNum ==> %s\n", strDesc);
	}
	//========================================================================
	// Close and try next one.
	//========================================================================
	fclose(file);
	libusb_close (devHandle);
	devHandle = NULL;
	libusb_exit (NULL);
	return 0;

}
