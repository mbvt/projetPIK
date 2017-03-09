#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

#define vendorId 0x0c45
#define productId 0x0101

int main ()
{
	libusb_device                    **devList = NULL;
	libusb_device                    *devPtr = NULL;
	libusb_device_handle             *devHandle = NULL;

	//static struct usb_device *find_device(uint16_t vendor, uint16_t product);

	struct libusb_device_descriptor  devDesc;
//	struct libusb_config_descriptor	 confDesc;
	//	int nb_usb = 10;
	//	array_desc = calloc(nb_usb, sizeof (struct SIS));
	//	struct SIS *ptr_SIS;

	unsigned char              strDesc[256];
	ssize_t                    idx = 2;
	ssize_t			   numUsbDevs = 0;
	int                        retVal = 0;
//	int			  retValDesc = 0;
//	uint8_t config_index = 8;

	FILE* file = NULL;
	file = fopen("result_desciption_clavier.txt","wr");	

	retVal = libusb_init (NULL);

	numUsbDevs = libusb_get_device_list(NULL, &devList);

	devPtr = devList[idx];
	retVal = libusb_open (devPtr, &devHandle);

	retVal = libusb_get_device_descriptor (devPtr, &devDesc);
	fprintf(file,"id = %zd \n", idx);
	//=====================================================================
        // 				bLength.
        //=====================================================================
        fprintf (file,"bLength, Size of this descriptor = 0x%02x\n", devDesc.bLength);
        if (devDesc.bLength > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle,devDesc.bLength, strDesc, 256);
                fprintf(file, "%s\n\n",  strDesc);
        }
	
	//=====================================================================
        // 			     bDescriptorType
        //=====================================================================
        fprintf (file,"bDescriptorType, Descriptor type = 0x%02x\n", devDesc.bDescriptorType );
        if (devDesc.bDescriptorType > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDescriptorType, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        // 				bcdUSB 
        //=====================================================================
        fprintf (file,"bcdUSB, USB specification release number in binary-coded decimal = 0x%04x\n", devDesc.bcdUSB );
        if (devDesc.bcdUSB > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdUSB, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
	
	//=====================================================================
        //                          bDeviceClass 
        //=====================================================================
        fprintf (file,"bDeviceClass, USB-IF class code for the device = 0x%02x\n", devDesc.bDeviceClass);
        if (devDesc.bDeviceClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceClass, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }
	
	//=====================================================================
        //                          bDeviceSubClass 
        //=====================================================================
        fprintf (file,"bDeviceSubClass, USB-IF subclass code for the device, qualified by the bDeviceClass value  = 0x%02x\n", devDesc.bDeviceSubClass);
        if (devDesc.bDeviceSubClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceSubClass, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        //                          bDeviceProtocol 
        //=====================================================================
        fprintf (file,"bDeviceProtocol, USB-IF protocol code for the device, qualified by the bDeviceClass and bDeviceSubClass values  = 0x%02x\n", devDesc.bDeviceProtocol);
        if (devDesc.bDeviceProtocol > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceProtocol, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        //                          bMaxPacketSize0 
        //=====================================================================
        fprintf (file,"bMaxPacketSize0, Maximum packet size for endpoint 0  = 0x%02x\n", devDesc.bMaxPacketSize0);
        if (devDesc.bMaxPacketSize0 > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bMaxPacketSize0, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        //                          idVendor 
        //=====================================================================
        fprintf (file,"idVendor, USB-IF vendor ID = 0x%04x\n", devDesc.idVendor);
        if (devDesc.idVendor > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idVendor, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        //                          idProduct 
        //=====================================================================
        fprintf (file,"idProduct, USB-IF product ID.  = 0x%04x\n", devDesc.idProduct);
        if (devDesc.idProduct > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idProduct, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
        //                          bcdDevice 
        //=====================================================================
        fprintf (file,"bcdDevice, USB-IF product ID.  = 0x%04x\n", devDesc.bcdDevice);
        if (devDesc.bcdDevice > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdDevice, strDesc, 256);
                fprintf(file, " %s\n\n",  strDesc);
        }

	//=====================================================================
	//			    iManufacturer
	//=====================================================================
	fprintf (file,"iManufacturer, Index of string descriptor describing manufacturer = 0x%02x\n", devDesc.iManufacturer);
	if (devDesc.iManufacturer > 0)
	{
		retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iManufacturer, strDesc, 256);

		fprintf(file, " %s\n\n",  strDesc);
	}

	//========================================================================
	// 				iProduct
	//========================================================================

	fprintf (file, "iProduct, Index of string descriptor describing product  = 0x%02x\n", devDesc.iProduct);
	if (devDesc.iProduct > 0)
	{
		retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
		fprintf (file, "%s\n\n", strDesc);
	}

	//==================================================================
	// 			      iSerialNumber
	//==================================================================

	fprintf (file,"iSerialNumber, Index of string descriptor containing device serial number = 0x%02x\n", devDesc.iSerialNumber);
	if (devDesc.iSerialNumber > 0)
	{
		retVal = libusb_get_string_descriptor_ascii
			(devHandle, devDesc.iSerialNumber, strDesc, 256);
		fprintf (file,"%s\n\n", strDesc);
	}
	
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

	//========================================================================
	// Close and try next one.
	//========================================================================
	fclose(file);
	libusb_close (devHandle);
	devHandle = NULL;
	libusb_exit (NULL);
	return 0;

}


