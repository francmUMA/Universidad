#! /bin/bash

if [ -f $1 -a -x $1 ]    
then
    echo "$1 es un archivo ejecutable"
else 
    echo "$1 no es un arhivo ejecutable"
fi
