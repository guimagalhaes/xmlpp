TARGET	= libxml++.so
CC	= g++
CFLAGS	= -Wall -DLINUX `pkg-config --cflags libxml-2.0`
LDLIBS	= `pkg-config --libs libxml-2.0`
OBJS	= xml_parser.o xml_reader.o xml_writer.o
SUBDIRS	= tests

INSTALL_DIR = usr/lib
INCLUDE_DIR = usr/include

CFLAGS += -fPIC
LDFLAGS = -shared -Wl,-soname,$(TARGET)

ifdef RELEASE
CFLAGS += -O2
else
CFLAGS += -g -DDEBUG
endif

CFLAGS += -I../common

all:	main subdirs

main:	$(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)
#ln -sf $(TARGET) $(TARGET).1

xml_parser.o: \
	xml_parser.h \
	fail_base.h \
	xml_parser.cpp
	$(CC) $(CFLAGS) -c -o $*.o $*.cpp

xml_reader.o: \
	xml_reader.h \
	xml_reader.cpp
	$(CC) $(CFLAGS) -c -o $*.o $*.cpp

xml_writer.o: \
	xml_writer.h \
	xml_writer.cpp
	$(CC) $(CFLAGS) -c -o $*.o $*.cpp

subdirs:
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir; \
	done

install:
	mkdir -p $(INSTALL_DIR)
	mkdir -p $(INCLUDE_DIR)
	cp -f $(TARGET) $(INSTALL_DIR)/$(TARGET)	
	cp -f xml_parser.h $(INCLUDE_DIR)/xml_parser.h
	cp -f xml_reader.h $(INCLUDE_DIR)/xml_reader.h
	cp -f xml_writer.h $(INCLUDE_DIR)/xml_writer.h
	cp -f xml_rw.h $(INCLUDE_DIR)/xml_rw.h

install_debian:
	mkdir -p $(DESTDIR)/mlibs/$(INSTALL_DIR)
	mkdir -p $(DESTDIR)/mlibs-dev/$(INCLUDE_DIR)
	cp -f $(TARGET) $(DESTDIR)/mlibs/$(INSTALL_DIR)/$(TARGET)
	cp -f xml_parser.h $(DESTDIR)/mlibs-dev/$(INCLUDE_DIR)/xml_parser.h
	cp -f xml_reader.h $(DESTDIR)/mlibs-dev/$(INCLUDE_DIR)/xml_reader.h
	cp -f xml_writer.h $(DESTDIR)/mlibs-dev/$(INCLUDE_DIR)/xml_writer.h
	cp -f xml_rw.h $(DESTDIR)/mlibs-dev/$(INCLUDE_DIR)/xml_rw.h

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)
	rm -f $(INCLUDE_DIR)/xml_parser.h
	rm -f $(INCLUDE_DIR)/xml_reader.h
	rm -f $(INCLUDE_DIR)/xml_writer.h
	rm -f $(INCLUDE_DIR)/xml_rw.h
	
clean:
	for dir in $(SUBDIRS); do \
	$(MAKE) -C $$dir clean; \
	done
	-rm -f $(OBJS) *~ core $(TARGET)*
