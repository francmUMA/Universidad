#! /usr/bin/bash

#ejercicio 1
string="Hola mundo"     #No se pueden dejar espacios despues del igual o antes
echo $string

#ejercicio 2
if [ -d $1 ]              #despues del if se pone un comando
then 
    echo "$1 es un directorio"
else 
    echo "$1 no es un directorio"
fi

#ejercicio 3
#while [ -d $1 ]
#do
    #echo "$1 es un directorio"
    #shift
#done

#ejercicio 4
for i in {1..10}
do
    echo $i
done

#ejercicio 5
count=$(ls /home/fran | wc -l)
echo $count
count=$(expr $count - 1)
echo $count
count=$(($count - 1))
echo  $count
