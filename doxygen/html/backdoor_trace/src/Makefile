target_svr=bd_svr
target_cli=bd_cli

ifeq ($(V),1)
Q=
else
Q=@
endif

target_svr_cc=$(CC)
target_cli_cc=$(HOST_CC)

libdirs=tools socket_tools handle cmd_tools
basic_srcs=$(foreach d, $(libdirs), $(wildcard $(d)/*.c))

target_svr_srcs=$(basic_srcs) svr.c
target_cli_srcs=$(basic_srcs) cli.c

cflags=-Iinclude #--save-temp

all: target_svr target_cli

target_%: 
	$(Q) $($@_cc) $(cflags) -o $($@) $($@_srcs)

clean: 
	$(Q) rm -rf *.[odais]
	$(Q) rm -rf $(target_svr) $(target_cli)

