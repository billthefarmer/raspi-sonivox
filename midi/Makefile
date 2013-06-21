# Makefile

CC = gcc

CFLAGS = -O2 -L. -Wl,-R.
LIBS = -lsonivox -lasound -lpthread
ULIBS = -lmidi

all:	libmidi.so playmidi

libmidi.so:	midi.c
	$(CC) -o $@ $< --shared $(CFLAGS) $(LIBS)

playmidi:	playmidi.c
	$(CC) -o $@ $< $(CFLAGS) $(ULIBS)
