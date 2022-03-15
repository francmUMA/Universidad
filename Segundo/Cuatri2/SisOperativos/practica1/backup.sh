#!/bin/bash
if [ ! -f "$1" ]	        # Chequea si el parámetro de entrada representa un fichero que existe
then				        # En caso de no existir, da un mensaje comunicándolo
	echo "$1 no existe" 
else				        # En caso de existir el fichero ...
	A=$(ls $1* | wc -w)	    # Lista los ficheros que comienzan por el nombre dado como
						    # parámetro y cuenta cuantos hay y lo almacena en A
	if [ $A -ge 9 ] 		# Si hay 9 o mas, da un mensaje indicando que se ha
							# alcanzado el máximo numero de versiones
	then
		echo "Se ha superado el numero máximo de versiones"
	else					# Si no se ha alcanzado el maximo ...
		Num=`expr $A + 1` 	# Sumale 1 al numero de ficheros que comienzan
							# con ese nombre (A) para que sea la terminación 
							# de la nueva copia
		Version=$1.$Num 	# Compone el nombre del nuevo nombre de fichero
							# (Version) como el nombre original ($1) seguido por
							# "." y el numero actual de copia (Num)
		cp $1 $Version 		# Copia el fichero original ($1) con el nombre nuevo
	fi
fi

