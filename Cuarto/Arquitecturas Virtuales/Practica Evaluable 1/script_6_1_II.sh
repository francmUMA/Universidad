#!/bin/bash
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi
#Script 6.1.II:
#Borrado de una VM existente en cli

#Imprimir su uso
if [ ! "$#" -gt "0" ]; then
    echo "Para poder ejecutar el script es necesario introducir algunos parámetros"
    echo "sh script_6_1.sh <nombre_maquina>"
    echo "  nombre_maquina: nombre de la máquina a borrar"
    exit 0
fi

#Comprobar si existe la máquina en cuestión
if ! vim-cmd vmsvc/getallvms | grep "$1"; then
    echo "ERROR: No existe ninguna máquina con ese nombre"
    exit 1
fi
ID=$(vim-cmd vmsvc/getallvms | grep "$1" | cut -d " " -f 1)
echo "$ID"

#Solicitar confirmación de borrado
echo "¿Está seguro de que desea borrar la máquina $1? (s/n)"
read -r CONFIRM
if [ "$CONFIRM" != "s" ]; then
    echo "Abortando borrado de la máquina $1"
    exit 0
fi

#Apagar la máquina
if vim-cmd vmsvc/power.getstate "$ID" | grep "Powered on"; then
    echo "Apagando la máquina..."
    if ! vim-cmd vmsvc/power.off "$ID"; then
        echo "ERROR: No se ha podido apagar la máquina"
        exit 1
    fi
fi

#Borrar la máquina (sugerencia: usar vim-cmd vmsvc/destroy)
echo "Borrando la máquina..."
if ! vim-cmd vmsvc/destroy "$ID"; then
    echo "ERROR: No se ha podido borrar la máquina"
    exit 1
fi

#Listar todas las máquinas para comprobar que se ha borrado
vim-cmd vmsvc/getallvms