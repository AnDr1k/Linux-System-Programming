#!/bin/sh

if [ $# -eq 2 ]; then

    writefile=$1
    writestr=$2

    mkdir -p $(dirname $writefile)
    echo "$writestr" > $writefile

    if [ ! -e $filesdir ]; then
        
        echo "ERROR: File could not be created."
        exit 1

    fi

    exit 0

else
    
    echo "ERROR: Invalid Number of Arguments."
    echo "Total number of arguments should be 2."
    echo "The order of the arguments should be:"
    echo "\t1) Full path to a file (including filename) on the filesystem."
    echo "\t2) Text string which will be written within the file."
    exit 1

fi