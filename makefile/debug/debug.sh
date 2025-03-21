#!/bin/bash
make -C ../vpath -f Makefile  -f - test << EOF
CFLAGS+=-static
test:
	@echo CFLAGS=\$(CFLAGS), LDFLAGS=\$(LDFLAGS), OBJS=\$(OBJS)
EOF
