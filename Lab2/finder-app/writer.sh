#!/bin/sh
#
if [ $# -ne 2 ]
then
  echo "Usage: $0 <file> <string>"
  exit 1
fi

writefile=$1
writestr=$2

echo ${writestr} > ${writefile}
if [ $? -ne 0 ] 
then
  echo "Failed to write file ${writefile}"
  exit 1
fi

exit 0
