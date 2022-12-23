#!/bin/sh
#
if [ $# -ne 2 ] 
then
  echo "Usage: $0 <dir> <string>"
  exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d ${filesdir} ]
then
  echo "Not a dir: ${filesdir}"
  exit 1
fi

nr_files=`ls -r ${filesdir} | wc -l`
nr_lines=`grep -R ${searchstr} ${filesdir} 2> /dev/null | wc -l`

echo "The number of files are ${nr_files} and the number of matching lines are ${nr_lines}" 

exit 0
