
ifeq ($(V),1)
Q=
else
Q=@
endif

EXE = src/bd_svr

dynamic: generic_exe_install

clean:
	$(Q) make -C src clean # 2>&1 | tee clean_$$(date '+%Y%m%d%H%M%S').log && sync

$(EXE):
	$(Q) CC=$(CC) HOST_CC=gcc make -C src V=$(V) # 2>&1 | tee compile_$$(date '+%Y%m%d%H%M%S').log && sync

CURR_DIR := $(shell pwd)
BUILD_DIR:=$(subst /onenet, /onenet,$(CURR_DIR))
BUILD_DIR:=$(word 1, $(BUILD_DIR))

include $(BUILD_DIR)/make.common


