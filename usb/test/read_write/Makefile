CC =gcc
CPPFLAGS= `pkg-config libusb-1.0 --libs --cflags`
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS= `pkg-config libusb-1.0 --libs --cflags`

SRC= read_write.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

read_write: ${PRG}

read_write: ${OBJ}

clean:
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG} 

