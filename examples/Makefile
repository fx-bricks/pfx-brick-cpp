
#OS = LINUX
OS = MACOSX
#OS = WINDOWS

PROG = pfxtest
INCDIR = ../src/

ifeq ($(OS), LINUX)
TARGET = $(PROG)
CC = gcc
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -I$(INCDIR)
LIBS = -lusb
else ifeq ($(OS), MACOSX)
#TARGET = $(PROG).dmg
TARGET = $(PROG)
SDK = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk
ARCH = -mmacosx-version-min=10.13 -arch x86_64
CC = clang
STRIP = strip
CFLAGS = -Wall -O2 -DOS_$(OS) -isysroot $(SDK) $(ARCH) -I$(INCDIR) -v
LIBS = $(ARCH) -Wl,-syslibroot,$(SDK) -framework IOKit -framework CoreFoundation -lc++
else ifeq ($(OS), WINDOWS)
TARGET = $(PROG).exe
CC = i586-mingw32msvc-gcc
STRIP = i586-mingw32msvc-strip
CFLAGS = -Wall -O2 -DOS_$(OS) -I$(INCDIR)
LIBS = -lhid -lsetupapi
endif

OBJS = $(PROG).o $(INCDIR)hid.o $(INCDIR)pfxbrick.o $(INCDIR)pfxconfig.o $(INCDIR)pfxhelpers.o $(INCDIR)pfxmsg.o $(INCDIR)pfxaction.o $(INCDIR)pfxfiles.o $(INCDIR)pfxdev.o

all: $(TARGET)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)
	$(STRIP) $(PROG)

$(PROG).exe: $(PROG)
	cp $(PROG) $(PROG).exe

pfxbrick.o: $(INCDIR)pfxbrick.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxconfig.o: $(INCDIR)pfxconfig.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxhelpers.o: $(INCDIR)pfxhelpers.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxmsg.o: $(INCDIR)pfxmsg.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxaction.o: $(INCDIR)pfxaction.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxfiles.o: $(INCDIR)pfxfiles.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

pfxdev.o: $(INCDIR)pfxdev.cpp $(INCDIR)pfxbrick.h
	$(CC) $(CFLAGS) -c -o $@ $<

hid.o: $(INCDIR)hid.c $(INCDIR)hidapi.h
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o $(PROG) $(PROG).exe
	rm -f $(INCDIR)*.o
