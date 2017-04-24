#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <libusb-1.0/libusb.h>


static struct libusb_device_handle *devh = NULL;

struct struct_key   {
                      uint16_t   num_w;
                      uint16_t   num_r;
                      char       array_nom[100];
                      int        number_key;
                      int        bit;
                      int        groupe;
                    };

struct struct_write {
                      uint16_t speed;
                      uint16_t red;
                      uint16_t green;
                      uint16_t blue;
                      uint16_t key;
                      libusb_device_handle *devh;
                    };


//____________________ R E A D ______________________________________
struct struct_key  read_chars(unsigned char * data, int size, struct struct_key key)
{
  int actual_length = 0;
  int rc;
  
  for (int i=0;i<size;data[i++]=0);;

  rc = libusb_bulk_transfer(devh, 0x81, data, 8, &actual_length,
      10);
  if(actual_length > 0)
  {
        for(int i = 0; i < actual_length; i++)
        {
            if(data[i] != 0)
            {
                //key.code_key = data[i];
                //key.position_bit = i;
                //fprintf(stdout, " code_key      : 0x%02x \n", key.code_key);
                //fprintf(stdout, " position_bit  : %d \n\n", key.position_bit);
            }
        }
        fprintf(stdout, "----------------------  \n");
        
  }
  (void)rc;
  return key;
}

//________________________C O L O R__________________________
void keybordcolor(struct struct_write *str)
{
  int rc = 0;
  
  uint16_t speed = str->speed;
  uint16_t red = str->red;
  uint16_t green = str->green;
  uint16_t blue = str->blue;       
  uint16_t key = str->key;
  libusb_device_handle *devh = str->devh; 
  
  unsigned char data_commit [] = { 0x11, 0xff, 0x0c, 0x5a, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  unsigned char data1 [] = { 0x12, 0xff, 0x0c , 0x3a,
    0x00, speed, 0x00, 0x0e, 
    key, red, green, blue, 
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };


  rc = libusb_control_transfer(devh, 0x21, 0X09, 0x0212, 1, 
      data1, sizeof(data1), 10); 
  printf("rc = %d \n", rc );

  rc = libusb_control_transfer(devh, 0x21, 0x09, 0x0211, 1, 
      data_commit, sizeof(data_commit), 10); 
  printf("rc = %d \n", rc );
}

//_____________________ U S B  -  I N I T ________________________
libusb_device_handle* USB_Init()
{
    libusb_device_handle  *devh = NULL;
    uint16_t  PRODUCT_ID = 0xc330;
    uint16_t VENDOR_ID = 0x046d;
    int res = 0;
    
    res = libusb_init(NULL);
    if(res < 0)
     fprintf(stderr, "Error initializing libusb: %s\n", libusb_error_name(res));
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
     for (int if_num = 0; if_num < 2; if_num++) 
     {
        if (libusb_kernel_driver_active(devh, if_num)) 
              libusb_detach_kernel_driver(devh, if_num);
        res = libusb_claim_interface(devh, if_num);
     }
  return devh;
}


//_____________________ U S B  -  C L O S E  ________________________
void USB_Close(libusb_device_handle *devh)
{
  libusb_release_interface(devh, 0);
  libusb_release_interface(devh, 1);

  libusb_attach_kernel_driver(devh, 0);
  libusb_attach_kernel_driver(devh, 1);

  if(devh)
    libusb_close(devh);
  libusb_exit(NULL);
}

void write_to_keybord (char *ptr_amine)
{
    char array_word [10];
    int i = 0;
    int len = 0;
    len = strlen(ptr_amine);
    while(*ptr_amine != '\0')
    {
      array_word[i] = *ptr_amine;
      ptr_amine++;
      printf(" ' %c ' \n", array_word[i]);
      i++;
    }
    printf("%s \n", ptr_amine);
    char array_numw [len];
    char *numw = get_numW_from_char(keymap);
}
//----------------------- M A I N ---------------------------
int main()
{

    libusb_device_handle  *devh = NULL;
    devh = USB_Init();
    struct struct_write *str = malloc (sizeof (struct struct_write ));
    //________ fin ini ==> debut de la phase de test _______________
    
    //recu de amine
    char *ptr_amine;
    ptr_amine = "brandon";
    // stoquer sur array_word
    
    struct matrix keymap = get_keymap("biblio");
    
    //____________read______________
    //  ° Write en fonction des char
    //  ° Lire char par char 
    //  ° Verifier si il y a maatch 
    //  ° en fonction de match ==> write 
    
    write_to_keybord(char *ptr_amine)

    //keybordcolor(str);
    free(str);
  /*unsigned char data_read[1024];
  struct struct_key key;
  while(1)
  {
    key = read_chars(data_read, 64, key);
    //sleep(0.1);
  }*/
  USB_Close(devh);
  return 0;
} 
