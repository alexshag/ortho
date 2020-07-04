
.PHONY: clean

CC=gcc
CFLAGS=-c -Wall -Wextra -pedantic -ansi -g -ggdb -O0
LDFLAGS=-lm
SOURCES= calculate.c coord_conv.c correction.c geo_inverse.c getmv.c getopt.c \
    strutils.c magmod.c main.c mygeod.c parse_mag.c parsewp.c pmdg.c wplist.c

OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ortho

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o

