
vpath %.c src 
vpath %.h inc
TARGET=sample
OBJS=main.o
CC=gcc
CFLAGS=-Wall -MMD -MP
CFLAGS+=-Iinc
LDFLAGS=-Wall
LIBS+=-pthread
.SUFFIXES: 
all: $(TARGET) 

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

%.o: %.c $(lastword $(MAKEFILE_LIST))
	echo $@, $<
	$(CC) $(CFLAGS) -o $@ -c $<

clean: 
	rm -rf *.[od] $(TARGET)

-include $(wildcard *.d)
