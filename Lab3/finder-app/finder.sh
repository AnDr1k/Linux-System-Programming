#!/bin/sh

if [ $# -eq 2 ]; then

    filesdir=$1
    searchstr=$2

    if [ ! -d $filesdir ]; then
        
        echo "ERROR: Invalid File Directory Path."
        echo "File directory path does not represent a directory on the filesystem."
        echo "Provide a valid file directory path."
        exit 1

    else

        num_files=$( grep -rl "$searchstr" $filesdir | wc -l )
        num_matching_lines=$( grep -r "$searchstr" $filesdir | wc -l )
        echo "The number of files are $num_files and the number of matching lines are $num_matching_lines."
        exit 0
        
    fi

else
    
    echo "ERROR: Invalid Number of Arguments."
    echo "Total number of arguments should be 2."
    echo "The order of the arguments should be:"
    echo "\t1) File Directory Path."
    echo "\t2) String to be searched in the specific directory path."
    exit 1

fi