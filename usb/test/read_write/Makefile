CC =gcc 
CPPFLAGS= `pkg-config libusb-1.0 --libs --cflags`
CFLAGS= -Wall -Wextra -std=c99 -O2 -pthread -g
LDFLAGS= -pthread 
LDLIBS= `pkg-config libusb-1.0 --libs --cflags `

SRC= read_write.c color.c script.c convert.c USB_Main.c
OBJ= ${SRC:.c=.o}

#DEP= ${SRC:.c=.d}

#PRG= ${SRC:.c=}

all: USB_Main

USB_Main:${OBJ}


#read_write: ${PRG}

#read_write: ${OBJ}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}

