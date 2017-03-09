#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

void save_info_device(struct libusb_device_descriptor devDesc,libusb_device_handle *devHandle, ssize_t idx)
{
	unsigned char              strDesc[256];
	int retVal = 0;
	
	FILE* file = NULL;
        file = fopen("result_desciption_clavier.txt","wr");
       retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
        fprintf (file, "	|------------------------------------------------------------|\n");
	fprintf(file,"	|			 	 			     |\n");
	fprintf(file,"	|			%s			     |\n",strDesc);
	fprintf(file,"	|							     |\n");
	fprintf(file,"	|____________________________________________________________|\n\n");
        
fprintf(file,"---------------------------------------------------------------\n\n");
	fprintf(file,"id = %zd \n\n", idx);
	fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                              bLength.
        //=====================================================================
        fprintf (file,"bLength, Size of this descriptor = 0x%02x\n", devDesc.bLength);
        if (devDesc.bLength > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle,devDesc.bLength, strDesc, 256);
                fprintf(file, "%s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                           bDescriptorType
        //=====================================================================
        fprintf (file,"bDescriptorType, Descriptor type = 0x%02x\n", devDesc.bDescriptorType );
        if (devDesc.bDescriptorType > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDescriptorType, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                              bcdUSB 
        //=====================================================================
        fprintf (file,"bcdUSB, USB specification release number in binary-coded decimal = 0x%04x\n", devDesc.bcdUSB );
        if (devDesc.bcdUSB > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdUSB, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
	//=====================================================================
        //                          bDeviceClass 
        //=====================================================================
        fprintf (file,"bDeviceClass, USB-IF class code for the device = 0x%02x\n", devDesc.bDeviceClass);
        if (devDesc.bDeviceClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceClass, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          bDeviceSubClass 
        //=====================================================================
        fprintf (file,"bDeviceSubClass, qualified by the bDeviceClass value  = 0x%02x\n", devDesc.bDeviceSubClass);
        if (devDesc.bDeviceSubClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceSubClass, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          bDeviceProtocol 
        //=====================================================================
        fprintf (file,"bDeviceProtocol,qualified by the bDeviceClass and bDeviceSubClass values  = 0x%02x\n", devDesc.bDeviceProtocol);
        if (devDesc.bDeviceProtocol > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceProtocol, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          bMaxPacketSize0 
        //=====================================================================
        fprintf (file,"bMaxPacketSize0, Maximum packet size for endpoint 0  = 0x%02x\n", devDesc.bMaxPacketSize0);
        if (devDesc.bMaxPacketSize0 > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bMaxPacketSize0, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
	//=====================================================================
        //                          idVendor 
        //=====================================================================
        fprintf (file,"idVendor, USB-IF vendor ID = 0x%04x\n", devDesc.idVendor);
        if (devDesc.idVendor > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idVendor, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          idProduct 
        //=====================================================================
        fprintf (file,"idProduct, USB-IF product ID.  = 0x%04x\n", devDesc.idProduct);
        if (devDesc.idProduct > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idProduct, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          bcdDevice 
        //=====================================================================
        fprintf (file,"bcdDevice, USB-IF product ID.  = 0x%04x\n", devDesc.bcdDevice);
        if (devDesc.bcdDevice > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdDevice, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //=====================================================================
        //                          iManufacturer
        //=====================================================================
        fprintf (file,"iManufacturer, string descriptor describing manufacturer = 0x%02x\n", devDesc.iManufacturer);
        if (devDesc.iManufacturer > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iManufacturer, strDesc, 256);

                fprintf(file, " %s\n\n",  strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
	//========================================================================
        //                              iProduct
        //========================================================================

        fprintf (file, "iProduct, Index of string descriptor describing product  = 0x%02x\n", devDesc.iProduct);
        if (devDesc.iProduct > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
                fprintf (file, "%s\n\n", strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //==================================================================
        //                            iSerialNumber
        //==================================================================

        fprintf (file,"iSerialNumber, string descriptor containing device serial number = 0x%02x\n", devDesc.iSerialNumber);
        if (devDesc.iSerialNumber > 0)
        {
                retVal = libusb_get_string_descriptor_ascii
                        (devHandle, devDesc.iSerialNumber, strDesc, 256);
                fprintf (file,"%s\n\n", strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
        //==================================================================
        //                            bNumConfigurations
        //==================================================================

        fprintf (file,"bNumConfigurations, Number of possible configurations = 0x%02x\n", devDesc.bNumConfigurations);
        if (devDesc.bNumConfigurations> 0)
        {
                retVal = libusb_get_string_descriptor_ascii
                        (devHandle, devDesc.bNumConfigurations, strDesc, 256);
                fprintf (file,"%s\n\n", strDesc);
        }
fprintf(file,"---------------------------------------------------------------\n\n");
	(void)retVal;
	 fclose(file);
}

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
	FILE* file = NULL;
	file = fopen("result_desciption_clavier.txt","wr");	

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
		save_info_device(devDesc, devHandle, idx);
	}
	else
	{
		printf("device not found");
	}
unsigned char ioBuffer[2];
retVal = libusb_control_transfer(
		devHandle, //handle
		0xC0, //bmRequestType
		51, //bRequest
		0, //wValue
		0, //wIndex
		ioBuffer, //data
		2, //wLength
        	0); //timeout	


	(void)retVal;
	fclose(file);
	libusb_close (devHandle);
	devHandle = NULL;
	libusb_exit (NULL);
	return 0;

}


