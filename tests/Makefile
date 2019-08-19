TARGET	 = teste
CC	 = g++
CFLAGS	 = -Wall -DLINUX
INCLUDES = -I.. `pkg-config --cflags libxml-2.0` -I../../common
LDLIBS	 = -lxml++ -L.. `pkg-config --libs libxml-2.0`
OBJS	 = teste.o

ifdef RELEASE
CFLAGS += -O2
else
CFLAGS += -g -DDEBUG
endif

all:	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $*.o $*.cpp

clean:
	-rm -f $(OBJS) *~ core $(TARGET) xml/new.xml

exec:
	LD_LIBRARY_PATH=../ ./$(TARGET) xml/teste.xml

leak_check:
	LD_LIBRARY_PATH=../ valgrind --leak-check=yes --show-reachable=yes -v ./$(TARGET) xml/teste.xml

debug:
	LD_LIBRARY_PATH=../ gdb ./$(TARGET)
