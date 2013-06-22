# Makefile

CC = gcc

CFLAGS = -O2 -L. -L/usr/local/lib -Wl,-R. -Wl,-R/usr/local/lib
LIBS = -lsonivox -lasound -lpthread
ULIBS = -lmidi

all:	libmidi.so playmidi sonivox

libmidi.so:	midi.c
	$(CC) -o $@ $< --shared $(CFLAGS) $(LIBS)

playmidi:	playmidi.c
	$(CC) -o $@ $< $(CFLAGS) $(ULIBS)

sonivox:	sonivox.c
	$(CC) -o $@ $< $(CFLAGS) $(ULIBS)
