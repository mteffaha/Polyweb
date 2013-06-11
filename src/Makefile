# Makefile pour le projet SI3 -- Serveur Web
#
#          Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 22-Apr-2013 12:19 (eg)
# Last file update:  2-Jun-2013 15:48 (eg)


CC      = gcc
CFLAGS  = -Wall -std=c99 -I../include -D_POSIX_C_SOURCE=200809L -g
LDFLAGS = -ldl

SRC     = $(wildcard *.c)
OBJ	= 

$(SRC:.c=.o)
EXE     = polyweb
LIB	= libpolyweb.a

all: $(EXE)

$(EXE): $(LIB)
	
	$(CC) -rdynamic -o $(EXE) $(LIB) $(LDFLAGS)
handler:
	$(CC) -c -I../include handler.c 
$(LIB): handler $(OBJ)
	rm -f $(LIB)
	ar cq $(LIB) $(OBJ)

clean:
	rm -f $(OBJ) $(LIB) $(EXE) *~
