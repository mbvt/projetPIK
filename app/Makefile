# Makefile
 
CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= 
 
SRC= app.c user.c profile.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
 
all: app
 
app: ${OBJ}
 
clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} app
 
-include ${DEP}
 
# END
