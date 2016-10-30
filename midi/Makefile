# Makefile

CC = gcc
RM = rm

CFLAGS = -O2 -fPIC -L/usr/local/lib -Wl,-R/usr/local/lib -Wl,-z,relro
LIBS = -lsonivox -lasound -lpthread
ULIBS = -lmidi

all:	libmidi.so playmidi sonivox

libmidi.so:	midi.c
	$(CC) -o $@ $< --shared $(CFLAGS) -Wl,-soname,libmidi.so $(LIBS)

playmidi:	playmidi.c
	$(CC) -o $@ $< $(CFLAGS) $(ULIBS)

sonivox:	sonivox.c
	$(CC) -o $@ $< $(CFLAGS) $(ULIBS)

clean:
	$(RM) *.so playmidi sonivox
