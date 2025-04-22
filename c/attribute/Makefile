
_@:=@
ifeq ($(V),1)
_@=
endif

DESTDIR=build
# SRCS=$(info $(wildcard src/*.c))
SRCS=$(foreach s,$(wildcard src/*.c),$(notdir $(s)))
TARGETS=$(foreach s,$(SRCS),$(patsubst %.c,%,$(s)))
# TARGETS=cleanup_func_enter_exit  cleanup_sample  packed_sample
vpath %.c src
vpath %.h inc
.PHONY: build
LDFLAGS=-Wall
CFLAGS=-Wall
CFLAGS+=-MMD -MP
CFLAGS+=-Iinc
LIBS=-pthread -lutil

all: $(DESTDIR) $(addprefix $(DESTDIR)/,$(TARGETS))

$(DESTDIR)/%: %.o
	$(_@) $(CC) $(LDFALGS) -o $@ $(addprefix $(DESTDIR)/,$^) $(LIBS)

clean: 
	$(_@) rm -rf $(DESTDIR)

$(DESTDIR):
	$(_@) mkdir -p $@

%.o: %.c Makefile
	$(_@) $(CC) $(CFLAGS) -o $(DESTDIR)/$@ -c $<

-include $(wildcard $(DESTDIR)/*.d)

