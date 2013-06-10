# Makefile pour le projet SI3 -- Serveur Web (tests)
#
#          Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 22-Apr-2013 12:19 (eg)
# Last file update:  2-Jun-2013 16:06 (eg)

CC      = gcc
CFLAGS  = -Wall -std=c99 -I../include -D_POSIX_C_SOURCE
LDFLAGS = -L../src -lpolyweb -lpthread

SRC     = $(wildcard *.c)
EXE     = $(SRC:.c=)
LIB	= ../src/libpolyweb.a

%: %.c
	$(CC) $(CFLAGS) -o $* $*.c $(LDFLAGS)

all: $(LIB) $(EXE)

$(LIB):
	@(cd ../src; make)

clean:
	/bin/rm -f $(OBJ) $(EXE) *~
