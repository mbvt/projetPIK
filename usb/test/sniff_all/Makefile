CC =gcc
CPPFLAGS= `pkg-config libusb-1.0 --libs --cflags`
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= `pkg-config libusb-1.0 --libs --cflags`

SRC= test_snif_usb.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

test_snif_usb: ${PRG}

test_snif_usb: ${OBJ}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}

