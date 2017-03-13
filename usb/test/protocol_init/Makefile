CC =gcc
CPPFLAGS= `pkg-config libusb-1.0 --libs --cflags`
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= `pkg-config libusb-1.0 --libs --cflags`

SRC= fd.c
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

fd: ${PRG}

fd: ${OBJ}

clean:
	rm -f *.o *.txt
	rm -f ${DEP}
	rm -f ${PRG}


