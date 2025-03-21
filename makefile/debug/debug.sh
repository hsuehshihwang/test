#!/bin/bash
make -C ../vpath -f Makefile  -f $(realpath ./append.mk) test
