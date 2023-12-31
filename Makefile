#############################################################################
# Makefile for building: qpptp
# Generated by qmake (1.07a) (Qt 3.3.8b) on: Mon May 11 22:27:24 2009
# Project:  qpptp.pro
# Template: app
# Command: $(QMAKE) -o Makefile qpptp.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i386 -mtune=generic -fasynchronous-unwind-tables  -DQT_NO_DEBUG -DQT_SHARED -DQT_TABLET_SUPPORT -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i386 -mtune=generic -fasynchronous-unwind-tables  -DQT_NO_DEBUG -DQT_SHARED -DQT_TABLET_SUPPORT -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt-3.3/mkspecs/default -I. -I$(QTDIR)/include -I.ui/ -I. -I.moc/
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = .obj/

####### Files

HEADERS = 
SOURCES = main.cpp
OBJECTS = .obj/main.o \
		.obj/qpptp.o \
		.obj/qmake_image_collection.o
FORMS = qpptp.ui
UICDECLS = .ui/qpptp.h
UICIMPLS = .ui/qpptp.cpp
SRCMOC   = .moc/moc_qpptp.cpp
OBJMOC = .obj/moc_qpptp.o
DIST	   = qpptp.pro
QMAKE_TARGET = qpptp
DESTDIR  = 
TARGET   = qpptp

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: qpptp.pro  /usr/lib/qt-3.3/mkspecs/default/qmake.conf /usr/lib/qt-3.3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile qpptp.pro
qmake: 
	@$(QMAKE) -o Makefile qpptp.pro

dist: 
	@mkdir -p .obj/qpptp && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .obj/qpptp/ && $(COPY_FILE) --parents qpptp_ja.ts .obj/qpptp/ && $(COPY_FILE) --parents qpptp.png .obj/qpptp/ && $(COPY_FILE) --parents qpptp.ui.h .obj/qpptp/ && ( cd `dirname .obj/qpptp` && $(TAR) qpptp.tar qpptp && $(GZIP) qpptp.tar ) && $(MOVE) `dirname .obj/qpptp`/qpptp.tar.gz . && $(DEL_FILE) -r .obj/qpptp

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS)
		-$(DEL_FILE) .ui/qmake_image_collection.cpp
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

.obj/main.o: main.cpp .ui/qpptp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/main.o main.cpp

.ui/qpptp.h: qpptp.ui 
	$(UIC) qpptp.ui -o .ui/qpptp.h

.ui/qpptp.cpp: .ui/qpptp.h qpptp.ui qpptp.ui.h 
	$(UIC) qpptp.ui -i qpptp.h -o .ui/qpptp.cpp

.obj/qpptp.o: .ui/qpptp.cpp qpptp.ui.h \
		.ui/qpptp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qpptp.o .ui/qpptp.cpp

.obj/moc_qpptp.o: .moc/moc_qpptp.cpp  .ui/qpptp.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_qpptp.o .moc/moc_qpptp.cpp

.moc/moc_qpptp.cpp: $(MOC) .ui/qpptp.h
	$(MOC) .ui/qpptp.h -o .moc/moc_qpptp.cpp

.obj/qmake_image_collection.o: .ui/qmake_image_collection.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qmake_image_collection.o .ui/qmake_image_collection.cpp

.ui/qmake_image_collection.cpp: qpptp.png
	$(UIC)  -embed qpptp qpptp.png -o .ui/qmake_image_collection.cpp

####### Install

install:  

uninstall:  

