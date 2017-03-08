#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

int main ()
{
	libusb_device                    **devList = NULL;
	libusb_device                    *devPtr = NULL;
	libusb_device_handle             *devHandle = NULL;

	struct libusb_device_descriptor  devDesc;
	//struct libusb_device_handle 	 *devHandle;

	ssize_t                    idx = 0;
	ssize_t			   numUsbDevs = 0;
	ssize_t			   compt = 0;
	int			   device_found = 0;
	int			   retVal;
	//---------------------------------------------------------------------//
	uint16_t		   productId = 0x8060;   // 0x8060   //id= 4 
	uint16_t		   ventorId = 0x0c45;
	//---------------------------------------------------------------------//

	retVal = libusb_init (NULL);
	numUsbDevs = libusb_get_device_list(NULL, &devList);
	
	while((devDesc.idVendor != ventorId) && (devDesc.idProduct != productId) && (idx < numUsbDevs))
	{
	
		devPtr = devList[idx];
	        retVal = libusb_open (devPtr, &devHandle);
        	retVal = libusb_get_device_descriptor (devPtr, &devDesc);
		idx ++;	
		if((devDesc.idVendor != ventorId) && (devDesc.idProduct != productId))
		{
			device_found = 1;
		}
	}

	if(device_found == 1)
	{
		printf("device found");
	}
	else
	{
		printf("device not found");
	}
	


	(void)retVal;
	fclose(file);
	libusb_close (devHandle);
	devHandle = NULL;
	libusb_exit (NULL);
	return 0;

}


