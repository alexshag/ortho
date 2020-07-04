
.PHONY: clean

CC=cl.exe
LD=link.exe
CFLAGS= /c /Ic:\vc98\include
LDFLAGS=/LIBPATH:c:\vc98\lib /OUT:ortho.exe
SOURCES= calculate.c coord_conv.c correction.c geo_inverse.c getmv.c getopt.c \
    strutils.c magmod.c main.c mygeod.c parse_mag.c parsewp.c pmdg.c wplist.c

OBJECTS=$(SOURCES:.c=.obj)
EXECUTABLE=ortho.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS)

.c:
	$(CC) $(CFLAGS) $< $@

clean:
	del *.obj
	del *.exe

