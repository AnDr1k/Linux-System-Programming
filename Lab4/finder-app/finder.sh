#!/bin/sh

filesdir=$1
searchstr=$2

if [ $# -lt 2 ] ; then
	return 1
fi

if ! [ -d $filesdir ] ; then
	echo Not a directory
	return 1
fi

FILES=`egrep -nRil $searchstr $filesdir | wc -l`
LINES=`egrep -nRi $searchstr $filesdir | wc -l`

echo The number of files are $FILES and the number of matching lines are $LINES
