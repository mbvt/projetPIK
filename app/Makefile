# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=600
#CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS=

#SRC= app.c user.c stat.c level.c str_mysql.c
SRC= app.c level.c
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
