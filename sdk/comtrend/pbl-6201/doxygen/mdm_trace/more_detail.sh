#!/bin/bash

rm -rf Doxyfile* docs src
mkdir -p src
BASE=~/work/comtrend/sdk/Opensync_3.2_L07p2.remote_test
ln -sf ${BASE}/userspace
ln -sf ${BASE}/userspace/private/apps/mdm src/
ln -sf ${BASE}/userspace/private/libs/cms_core src/
ln -sf ${BASE}/userspace/private/libs/cms_cli src/
doxygen -g

INPUT=./src
NAME="Ralph Project"
<< EOF
PROJECT_NAME           = ${NAME}
OUTPUT_DIRECTORY       = docs
RECURSIVE              = YES
GENERATE_HTML          = YES
GENERATE_LATEX         = NO
EXTRACT_ALL            = YES
INPUT                  = ${INPUT}
HAVE_DOT               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
SOURCE_BROWSER         = YES
INLINE_SOURCES         = YES
REFERENCED_BY_RELATION = YES
REFERENCES_RELATION    = YES
VERBATIM_HEADERS       = YES
HAVE_DOT               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES
EOF

sed -ie "s%^PROJECT_NAME *=.*%PROJECT_NAME=\"${NAME}\"%" Doxyfile
sed -ie "s%^OUTPUT_DIRECTORY *=.*%OUTPUT_DIRECTORY=docs%" Doxyfile
sed -ie "s%^RECURSIVE *=.*%RECURSIVE=YES%" Doxyfile
sed -ie "s%^GENERATE_HTML *=.*%GENERATE_HTML=YES%" Doxyfile
sed -ie "s%^GENERATE_LATEX *=.*%GENERATE_LATEX=NO%" Doxyfile
sed -ie "s%^EXTRACT_ALL *=.*%EXTRACT_ALL=YES%" Doxyfile
sed -ie "s%^INPUT *=.*%INPUT=./src ./include%" Doxyfile
sed -ie "s%^HAVE_DOT *=.*%HAVE_DOT=YES%" Doxyfile
sed -ie "s%^CALL_GRAPH *=.*%CALL_GRAPH=YES%" Doxyfile
sed -ie "s%^CALLER_GRAPH *=.*%CALLER_GRAPH=YES%" Doxyfile
sed -ie "s%^SOURCE_BROWSER *=.*%SOURCE_BROWSER=YES%" Doxyfile
sed -ie "s%^INLINE_SOURCES *=.*%INLINE_SOURCES=YES%" Doxyfile
sed -ie "s%^REFERENCED_BY_RELATION *=.*%REFERENCED_BY_RELATION=YES%" Doxyfile
sed -ie "s%^REFERENCES_RELATION *=.*%REFERENCES_RELATION=YES%" Doxyfile
sed -ie "s%^VERBATIM_HEADERS *=.*%VERBATIM_HEADERS=YES%" Doxyfile
sed -ie "s%^HAVE_DOT *=.*%HAVE_DOT=YES%" Doxyfile
sed -ie "s%^CALL_GRAPH *=.*%CALL_GRAPH=YES%" Doxyfile
sed -ie "s%^CALLER_GRAPH *=.*%CALLER_GRAPH=YES%" Doxyfile
doxygen Doxyfile

DISPLAY=:1 xdg-open docs/html/index.html


