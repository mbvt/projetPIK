# Makefile
CC=gcc
CPPFLAGS= `pkg-config libusb-1.0 --libs --cflags` `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -export-dynamic
CFLAGS= $(shell pkg-config --cflags sqlite3) -Wall -Wextra -std=c99 -O3 -g
LDFLAGS=
LDLIBS= $(shell pkg-config --libs sqlite3) `pkg-config --libs gtk+-3.0`\
				`pkg-config --libs sdl` -lSDL_image -export-dynamic -lm\
        `pkg-config libusb-1.0 --libs --cflags`

SRC= main.c\
		 str_mysql.c user.c app.c level.c\
		 ./ihm/quit_button.c ./ihm/inscription.c ./ihm/connexion.c ./ihm/game.c\
     ./usb/read_write.c ./usb/color.c ./usb/script.c\
     ./usb/convert.c ./usb/USB_Main.c 

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ}
	rm -f ${DEP}
	rm -f main

# END Makefile
