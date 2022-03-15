#! /bin/bash
for file in $(ls $1)
do
    num_versiones=$(ls *$file | wc -w)
    if [ $num_versiones -ge 9 ]
    then
        echo "$file ha alcanzado el numero maximo de versiones"
    else
        fecha=$(date "+%y%m%d")
        nombre_nuevo="${fecha}_${file}"
        cp $file $nombre_nuevo
    fi
done
shift
