#! /bin/bash
for i in `ls -R $1`
do
    if [ -f $1/$i ]
    then 
        echo "$i -> Es un fichero"
    elif [ -d $1/$i ]
    then
        echo "$i -> Es un directorio"
    fi
done

