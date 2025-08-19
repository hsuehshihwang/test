
vpath %.c src
vpath %.h inc

_@:=@
ifeq ($(V),1)
_@=
endif

DESTDIR=build
TARGET=$(DESTDIR)/sample
SRCS=main.c
OBJS=$(foreach s,$(SRCS),$(patsubst %.c,$(DESTDIR)/%.o,$(s)))

CC=gcc
CFLAGS=-Wall -MMD -MP -Iinc
LDFLAGS=-Wall
LIBS=-pthread

.SUFFIXES: 

.PHONY: 

all: $(DESTDIR) $(TARGET)

clean: 
	$(_@) rm -rf $(DESTDIR)

$(TARGET): $(OBJS)
	$(_@) $(CC) $(LDFLAGS) -o $@ $< $(LIBS)

$(DESTDIR)/%.o: %.c
	$(_@) $(CC) $(CFLAGS) -o $@ -c $<

$(DESTDIR): 
	$(_@) mkdir -p $@

-include $(DESTDIR/*.d)

