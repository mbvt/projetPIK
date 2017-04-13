# Makefile
CC=gcc

CPPFLAGS=  `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl`  -export-dynamic
CFLAGS= -Wall -Wextra -std=c99 -O1 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl`  -lSDL_image -export-dynamic -lm

SRC= main.c
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
