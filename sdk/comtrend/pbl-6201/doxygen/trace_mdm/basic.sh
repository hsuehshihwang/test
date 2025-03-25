#!/bin/bash

rm -rf Doxyfile* docs
doxygen -g

INPUT=./src ./include
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
EOF

sed -ie "s%^PROJECT_NAME *=.*%PROJECT_NAME=\"${NAME}\"%" Doxyfile
sed -ie "s%^OUTPUT_DIRECTORY *=.*%OUTPUT_DIRECTORY=docs%" Doxyfile
sed -ie "s%^RECURSIVE *=.*%RECURSIVE=YES%" Doxyfile
sed -ie "s%^GENERATE_HTML *=.*%GENERATE_HTML=YES%" Doxyfile
sed -ie "s%^GENERATE_LATEX *=.*%GENERATE_LATEX=NO%" Doxyfile
sed -ie "s%^EXTRACT_ALL *=.*%EXTRACT_ALL=YES%" Doxyfile
sed -ie "s%^INPUT *=.*%INPUT=${INPUT}%" Doxyfile
sed -ie "s%^HAVE_DOT *=.*%HAVE_DOT=YES%" Doxyfile
sed -ie "s%^CALL_GRAPH *=.*%CALL_GRAPH=YES%" Doxyfile
sed -ie "s%^CALLER_GRAPH *=.*%CALLER_GRAPH=YES%" Doxyfile

doxygen Doxyfile

DISPLAY=:1 xdg-open docs/html/index.html


