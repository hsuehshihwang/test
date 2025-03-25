#!/bin/sh

usage(){
	echo "$0 <head file name>"
}

if [ "$#" != "1" ]; then 
	usage 
	exit;   
fi



head_def=`echo $1 | tr "[a-z]" "[A-Z]"`

echo -en "#ifndef __${head_def}_H__\n" > $1.h
echo -en "#define __${head_def}_H__\n" >> $1.h
echo -en "#endif /*__${head_def}_H__*/\n" >> $1.h


