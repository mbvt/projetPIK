# Makefile
CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -export-dynamic
CFLAGS= $(shell pkg-config --cflags sqlite3) -Wall -Wextra -std=c99 -O3 -g
LDFLAGS=
LDLIBS= $(shell pkg-config --libs sqlite3) `pkg-config --libs gtk+-3.0`\
				`pkg-config --libs sdl` -lSDL_image -export-dynamic -lm

SRC= main.c str_mysql.c user.c

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
