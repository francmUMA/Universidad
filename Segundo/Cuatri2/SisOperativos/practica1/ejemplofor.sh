#! /bin/bash
for i in `ls $1`
do
    if [ ! -e $1/$i  ]
    then
        echo "$i no existe"
    fi
    if [ -f $1/$i ]
    then 
        echo "$i -> Es un fichero"
    elif [ -d $1/$i ]
    then
        echo "$i -> Es un directorio"
    fi
done

