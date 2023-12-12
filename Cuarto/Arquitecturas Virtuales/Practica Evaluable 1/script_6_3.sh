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

ID_ORIGEN=$(vim-cmd vmsvc/getallvms | grep -w "$1" | cut -d " " -f 1)

#Comprobar que la máquina origen tiene uno y sólo un snapshot
if vim-cmd vmsvc/get.snapshot "$ID_ORIGEN" | grep -w "childSnapshotList"; then
    echo "ERROR: La máquina origen tiene más de un snapshot"
    exit 1
fi

if ! vim-cmd vmsvc/get.snapshot "$ID_ORIGEN" | grep -w "id"; then
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
echo "DISK_NAME = $DISK_NAME"
if ! cp "$DATASTOREPATH/$1/$DISK_NAME" "$DATASTOREPATH/$2/$DISK_NAME"; then
    echo "ERROR: No se ha podido copiar el fichero .vmdk"
    exit 1
fi

DISK_NAME_NO_EXT=$(echo "$DISK_NAME" | cut -d "." -f 1)
echo "DISK_NAME_NO_EXT = $DISK_NAME_NO_EXT"
# fichero delta
if ! cp "$DATASTOREPATH/$1/$DISK_NAME_NO_EXT-delta.vmdk" "$DATASTOREPATH/$2/$DISK_NAME_NO_EXT-delta.vmdk"; then
    echo "ERROR: No se ha podido copiar el fichero delta del snapshot"
    exit 1
fi
 
#Cambiar la referencia del “parent disk” del fichero de definición del disco 
#que debe de apuntar al de la máquina origen (en el directorio ..) 
#Hay que cambiar el campo parentFileNameHint del fichero .vmdk por el nombre del padre en el directorio de la máquina origen
PARENT_NAME=$DATASTOREPATH/$1/$1.vmdk
echo "PARENT_NAME = $PARENT_NAME"
if ! sed -i 's/parentFileNameHint=.*/parentFileNameHint='"$PARENT_NAME"'/g' $DATASTOREPATH/$2/$DISK_NAME > /dev/null; then
    echo "ERROR: No se ha podido cambiar el campo parentFileNameHint del fichero .vmdk"
    exit 1
fi
 
#Generar un fichero .vmsd (con nombre del clon) en el que se indica que 
#es una máquina clonada. 
# 
#Coge un fichero .vsmd de un clon generado con VMware Workstation para ver 
#el formato de este archivo 
# 
#Si no se genera el fichero .vmsd, al destruir el clon también se borra el 
#disco base del snapshot, lo cual no es deseable ya que pertenece a la máquina  
#origen 
touch "$DATASTOREPATH/$2/$2.vmsd"
echo ".encoding = \"UTF-8\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot.lastUID = \"1\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot.current = \"1\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.uid = \"1\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.filename = \"$DISK_NAME_NO_EXT.vmdk\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.displayName = \"Snapshot\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.type = \"1\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.createTimeHigh = \"0\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.createTimeLow = \"0\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.numDisks = \"1\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.disk0.fileName = \"$DISK_NAME_NO_EXT-delta.vmdk\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.disk0.node = \"scsi0:0\"" >> "$DATASTOREPATH/$2/$2.vmsd"
echo "snapshot0.disk0.numSnapshots = \"0\"" >> "$DATASTOREPATH/$2/$2.vmsd"

 
#Una vez que el directorio clon contiene todos los ficheros necesarios 
#hay que registrar la máquina clon (ESTO ES IMPRESCINDIBLE) 
if ! vim-cmd solo/registervm "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido registrar la máquina clon"
    #Borrar directorio
    if ! rm -rf "$DATASTOREPATH/$2"; then
        echo "ERROR: No se ha podido borrar el directorio"
    fi
    exit 1
fi 
echo "Máquina clonada correctamente"
 
 
#Listar todas las máquinas para comprobar que el clon está disponible 
vim-cmd vmsvc/getallvms
 
#ID de la máquina clon
ID_CLON=$(vim-cmd vmsvc/getallvms | grep -w "$2" | cut -d " " -f 1)

#Para terminar arranca el clon desde el cliente de vSphere
if ! vim-cmd vmsvc/power.on "$ID_CLON"; then
    echo "ERROR: No se ha podido arrancar la máquina clon"
    exit 1
fi
echo "Máquina clon arrancada correctamente"

#Apagar máquina
if ! vim-cmd vmsvc/power.off "$ID_CLON"; then
    echo "ERROR: No se ha podido apagar la máquina clon"
    exit 1
fi
echo "Máquina clon apagada correctamente"
