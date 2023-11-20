#!/bin/sh
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi 
#Script 6.3: 
#Creación de un Linked clone de una VM existente en cli 
 
#Directorio donde se ubican las máquinas
DATASTOREPATH=/vmfs/volumes/datastore1/mv-dest
 
#Imprimir su uso
if [ ! "$#" -gt "1" ]; then
    echo "Para poder ejecutar el script es necesario introducir algunos parámetros"
    echo "sh script_6_3.sh <nombre_maquina> <nombre_maquina_clon>"
    echo "  nombre_maquina: nombre de la máquina a clonar"
    echo "  nombre_maquina_clon: nombre de la máquina clon"
    exit 1
fi 

#Comprobar que existe la máquina origen a clonar
if ! vim-cmd vmsvc/getallvms | grep -w "$1"; then
    echo "ERROR: No existe ninguna máquina con el nombre de origen"
    exit 1
fi

#Comprobar que no existe la maquina clon
if vim-cmd vmsvc/getallvms | grep -w "$2"; then
    echo "ERROR: Ya existe una máquina con el nombre de destino"
    exit 1
fi

ID=$(vim-cmd vmsvc/getallvms | grep -w "$2" | cut -d " " -f 1)

#Comprobar que la máquina origen tiene uno y sólo un snapshot
if vim-cmd vmsvc/get.snapshot "$ID" | grep -w "childSnapshotList"; then
    echo "ERROR: La máquina origen tiene más de un snapshot"
    exit 1
fi

if ! vim-cmd vmsvc/get.snapshot "$ID" | grep -w "id"; then
    echo "ERROR: La máquina origen no tiene ningún snapshot"
    exit 1
fi

#Encontrar la ubicación e identificadores de la máquina a copiar 
#Copiar los ficheros de definición de la máquina origen a la máquina clon: 
# - fichero de configuración: .vmx, 
# - fichero de definición del disco: .vmdk 
# - fichero delta del snapshot 
# Nota: es necesario averiguar los nombres de estos ficheros  
#       a partir del fichero de configuración 

#Crear directorio
mkdir "$DATASTOREPATH/$2"

#Copiar ficheros
#.vmx
if ! cp "$DATASTOREPATH/$1/$1.vmx" "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido copiar el fichero .vmx"
    exit 1
fi

#.vmdk -- Snapshot --> El nombre del disco viene en el campo scsi0:0.fileName del .vmx
DISK_NAME=$(cat "$DATASTOREPATH/$2/$2.vmx" | grep "scsi0:0.fileName" | cut -d "\"" -f 2)
if ! cp "$DATASTOREPATH/$1/$DISK_NAME" "$DATASTOREPATH/$2/$DISK_NAME"; then
    echo "ERROR: No se ha podido copiar el fichero .vmdk"
    exit 1
fi

# fichero delta
if ! cp "$DATASTOREPATH/$1/$DISK_NAME-delta.vmdk" "$DATASTOREPATH/$2/$DISK_NAME-delta.vmdk"; then
    echo "ERROR: No se ha podido copiar el fichero delta del snapshot"
    exit 1
fi
 
#Sustituir los nombres de ficheros y sus respectivas referencias dentro de 
#estos por el nombre clon  
#¡Atención! Esto requiere un pequeño parsing del contenido  
#para sustituir aquellos campos de los ficheros de configuración que hacen #referencias a los ficheros. 
 
 
 
#Cambiar la referencia del “parent disk” del fichero de definición del disco 
#que debe de apuntar al de la máquina origen (en el directorio ..) 
 
 
#Generar un fichero .vmsd (con nombre del clon) en el que se indica que 
#es una máquina clonada. 
# 
#Coge un fichero .vsmd de un clon generado con VMware Workstation para ver 
#el formato de este archivo 
# 
#Si no se genera el fichero .vmsd, al destruir el clon también se borra el 
#disco base del snapshot, lo cual no es deseable ya que pertenece a la máquina  
#origen 
 
 
#Una vez que el directorio clon contiene todos los ficheros necesarios 
#hay que registrar la máquina clon (ESTO ES IMPRESCINDIBLE) 
 
 
 
#Listar todas las máquinas para comprobar que el clon está disponible 
 
 
 
#Para terminar arranca el clon desde el cliente de vSphere 