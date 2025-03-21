#!/bin/bash
make -C ../vpath -f $(realpath ./append.mk) test
