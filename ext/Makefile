#           Author: Erick Gallesio [eg@unice.fr]
#    Creation date: 25-Apr-2013 21:15 (eg)
# Last file update:  8-Jun-2013 22:15 (eg)

CC=gcc
CFLAGS=-Wall -std=c99 -I../include -D_POSIX_C_SOURCE=200809L -fPIC -shared

SRC     = $(wildcard *.c)
SO	= $(SRC:.c=.so)
MD	= $(wildcard *.md)

#%.so: %.o
#	gcc -shared -o $*.so $*.o

%.so: %.c
	$(CC) $(CFLAGS) -o  $*.so $*.c

# Pour l'edition de lien, il faut ajouter la bibliothèque libdl.so (option -ldl)
# main: main.o
# 	$(CC) -o main main.o -ldl
#

all:  $(SO) 

clean:
	rm -f  *.so *.o *~ $(HTML)

clobber: clean
