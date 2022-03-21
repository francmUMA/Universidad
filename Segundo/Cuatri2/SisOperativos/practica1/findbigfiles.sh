#!/bin/bash
for file in $(ls $1)
do
    if [ -d $file ]
    then ./findbigfiles.sh $1/$file $2
    fi
    size_file=$(stat $1/$file | grep "Tamaño:" | cut -f 2 -d ":" | cut -f 1)
    if [ $size_file -ge $2 ]
    then echo "$1/${file}: ${size_file} bytes"
    fi
done

