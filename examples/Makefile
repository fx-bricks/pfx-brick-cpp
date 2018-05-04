
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

OBJS = $(INCDIR)hid.o $(INCDIR)pfxbrick.o $(INCDIR)pfxconfig.o $(INCDIR)pfxhelpers.o $(INCDIR)pfxmsg.o $(INCDIR)pfxaction.o $(INCDIR)pfxfiles.o $(INCDIR)pfxdev.o

all: getinfo filedir lightfx changecfg eventlut filecopyto filecopyfrom fileremove

getinfo: getinfo.cpp $(OBJS)
	$(CC) -o getinfo getinfo.cpp $(OBJS) $(LIBS)
	$(STRIP) getinfo

changecfg: changecfg.cpp $(OBJS)
	$(CC) -o changecfg changecfg.cpp $(OBJS) $(LIBS)
	$(STRIP) changecfg

eventlut: eventlut.cpp $(OBJS)
	$(CC) -o eventlut eventlut.cpp $(OBJS) $(LIBS)
	$(STRIP) eventlut

filedir: filedir.cpp $(OBJS)
	$(CC) -o filedir filedir.cpp $(OBJS) $(LIBS)
	$(STRIP) filedir

filecopyto: filecopyto.cpp $(OBJS)
	$(CC) -o filecopyto filecopyto.cpp $(OBJS) $(LIBS)
	$(STRIP) filecopyto

filecopyfrom: filecopyfrom.cpp $(OBJS)
	$(CC) -o filecopyfrom filecopyfrom.cpp $(OBJS) $(LIBS)
	$(STRIP) filecopyfrom

fileremove: fileremove.cpp $(OBJS)
	$(CC) -o fileremove fileremove.cpp $(OBJS) $(LIBS)
	$(STRIP) fileremove

lightfx: lightfx.cpp $(OBJS)
	$(CC) -o lightfx lightfx.cpp $(OBJS) $(LIBS)
	$(STRIP) lightfx
  

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
	rm -f *.o getinfo filedir
	rm -f $(INCDIR)*.o
