# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=600 
<<<<<<< HEAD
CFLAGS= $(shell pkg-config --cflags sqlite3) -Wall -Werror -Wextra -std=c99 -O2 -g
=======
CFLAGS= -Wall -Werror -Wextra -std=c99 -O0 -g
>>>>>>> 3d9160254bafab3633e968e4ea608a34343aa9a0
LDFLAGS=
LDLIBS= $(shell pkg-config --libs sqlite3)


#SRC= app.c user.c stat.c level.c str_mysql.c
SRC= app.c user.c level.c str_mysql.c
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
