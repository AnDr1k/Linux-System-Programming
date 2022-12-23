#!/bin/sh

writefile=$1
writestr=$2

if [ $# -lt 2 ] ; then
	return 1
fi

FILE=$1
STRIPPED=`dirname $FILE`

if ! [ -f $STRIPPED ] ; then
	mkdir -p $STRIPPED
fi

echo $writestr > $writefile
