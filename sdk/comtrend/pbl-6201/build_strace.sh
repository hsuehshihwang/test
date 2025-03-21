#!/bin/bash

make_rules=$(cat <<'EOF'
CFLAGS+=-static
LDFAGS+=-static
debug: 
	@echo CFLAGS=\$(CFLAGS), LDFLAGS=\$(LDFLAGS)
EOF
)

make -C userspace/gpl/apps/strace -f Makefile -f - BUILD_STRACE=y << EOF
$make_rules
EOF

# make -C userspace/gpl/apps/strace -f Makefile -f - BUILD_STRACE=y debug << EOF
# CFLAGS+=-static
# LDFAGS+=-static
# debug: 
# 	@echo CFLAGS=\$(CFLAGS), LDFLAGS=\$(LDFLAGS)
# EOF

