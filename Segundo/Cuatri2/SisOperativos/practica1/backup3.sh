#!/bin/bash
for file_type in $@
do
    for file in $(ls *$file_type)
    do
        if [ ! -d ./backup ]
        then 
            mkdir backup
        fi
        cd backup
        fecha=$(date "+%y%m%d")
        if [ ! -d ./$fecha ]
        then
            mkdir $fecha
        fi
        cd $fecha
        num_version=$(($(ls *$file | wc -w) + 1))
        newName="${num_version}_$file"
        cp ../../$file $newName
        cd ../..
    done
done

