#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libusb-1.0/libusb.h>

void print_confg(struct libusb_device_descriptor devDesc,libusb_device_handle *devHandle, ssize_t idx)
{
	unsigned char              strDesc[256];
        int retVal = 0;
	printf("id = %zd \n", idx);
        //=====================================================================
        //                              bLength.
        //=====================================================================
        printf ("bLength, Size of this descriptor = 0x%02x\n", devDesc.bLength);
        if (devDesc.bLength > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle,devDesc.bLength, strDesc, 256);      
                printf("%s\n\n",  strDesc);
        }

        //=====================================================================
        //                           bDescriptorType
        //=====================================================================
        printf ("bDescriptorType, Descriptor type = 0x%02x\n", devDesc.bDescriptorType );
        if (devDesc.bDescriptorType > 0)
        {       
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDescriptorType, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                              bcdUSB 
        //=====================================================================
        printf ("bcdUSB, USB specification release number in binary-coded decimal = 0x%04x\n", devDesc.bcdUSB );
        if (devDesc.bcdUSB > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdUSB, strDesc, 256);      
                printf(" %s\n\n",  strDesc);
        }
	 //=====================================================================
        //                          bDeviceClass 
        //=====================================================================
        printf ("bDeviceClass, USB-IF class code for the device = 0x%02x\n", devDesc.bDeviceClass);
        if (devDesc.bDeviceClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceClass, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          bDeviceSubClass 
        //=====================================================================
        printf ("bDeviceSubClass, USB-IF subclass code for the device, qualified by the bDeviceClass value  = 0x%02x\n", devDesc.bDeviceSubClass);
        if (devDesc.bDeviceSubClass > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceSubClass, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          bDeviceProtocol 
        //=====================================================================
        printf ("bDeviceProtocol, USB-IF protocol code for the device, qualified by the bDeviceClass and bDeviceSubClass values  = 0x%02x\n", devDesc.bDeviceProtocol);
        if (devDesc.bDeviceProtocol > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bDeviceProtocol, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          bMaxPacketSize0 
        //=====================================================================
        printf ("bMaxPacketSize0, Maximum packet size for endpoint 0  = 0x%02x\n", devDesc.bMaxPacketSize0);
        if (devDesc.bMaxPacketSize0 > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bMaxPacketSize0, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }
	//=====================================================================
        //                          idVendor 
        //=====================================================================
        printf ("idVendor, USB-IF vendor ID = 0x%04x\n", devDesc.idVendor);
        if (devDesc.idVendor > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idVendor, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          idProduct 
        //=====================================================================
        printf ("idProduct, USB-IF product ID.  = 0x%04x\n", devDesc.idProduct);
        if (devDesc.idProduct > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.idProduct, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          bcdDevice 
        //=====================================================================
        printf ("bcdDevice, USB-IF.  = 0x%04x\n", devDesc.bcdDevice);
        if (devDesc.bcdDevice > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.bcdDevice, strDesc, 256);
                printf(" %s\n\n",  strDesc);
        }

        //=====================================================================
        //                          iManufacturer
        //=====================================================================
        printf ("iManufacturer, Index of string descriptor describing manufacturer = 0x%02x\n", devDesc.iManufacturer);
        if (devDesc.iManufacturer > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iManufacturer, strDesc, 256);

                printf(" %s\n\n",  strDesc);
        }
	//========================================================================
        //                              iProduct
        //========================================================================

        printf ("iProduct, Index of string descriptor describing product  = 0x%02x\n", devDesc.iProduct);
        if (devDesc.iProduct > 0)
        {
                retVal = libusb_get_string_descriptor_ascii( devHandle, devDesc.iProduct, strDesc, 256);
                printf ("%s\n\n", strDesc);
        }

        //==================================================================
        //                            iSerialNumber
        //==================================================================

        printf ("iSerialNumber, Index of string descriptor containing device serial number = 0x%02x\n", devDesc.iSerialNumber);
        if (devDesc.iSerialNumber > 0)
        {
                retVal = libusb_get_string_descriptor_ascii
                        (devHandle, devDesc.iSerialNumber, strDesc, 256);
                printf ("%s\n\n", strDesc);
        }

        //==================================================================
        //                            bNumConfigurations
        //==================================================================

        printf ("bNumConfigurations, Number of possible configurations = 0x%02x\n", devDesc.bNumConfigurations);
        if (devDesc.bNumConfigurations> 0)
        {
                retVal = libusb_get_string_descriptor_ascii
                        (devHandle, devDesc.bNumConfigurations, strDesc, 256);
                printf ("%s\n\n", strDesc);
        }
        (void)retVal;

}    

int main ()
{
	libusb_device                    **devList = NULL;
	libusb_device                    *devPtr = NULL;
	libusb_device_handle             *devHandle = NULL;

	struct libusb_device_descriptor  devDesc;
	//	int nb_usb = 10;
	//	struct SIS *ptr_SIS;

	ssize_t                    numUsbDevs = 0;      // pre-initialized scalars
	ssize_t                    idx = 0;
	int                        retVal = 0;
	
	printf ("*************************\n USB Experiment Program:\n*************************\n");
	retVal = libusb_init (NULL);
	numUsbDevs = libusb_get_device_list (NULL, &devList);

	while (idx < numUsbDevs)
	{
		printf ("\n[%zd]\n", idx+1);
		devPtr = devList[idx];

		retVal = libusb_open (devPtr, &devHandle);
		if (retVal == LIBUSB_SUCCESS)
		{
			retVal = libusb_get_device_descriptor (devPtr, &devDesc);
			printf("----------------------------------------------------------------\n");
			print_confg(devDesc, devHandle, idx);
		}

		libusb_close (devHandle);
		devHandle = NULL;
		idx++;
	}

	libusb_close (devHandle);
	libusb_exit (NULL);
	printf ("\n*************************\n        Done\n*************************\n");
	return 0;
}
