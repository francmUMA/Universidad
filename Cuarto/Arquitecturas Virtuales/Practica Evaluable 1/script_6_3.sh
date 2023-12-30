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
if ! vim-cmd vmsvc/getallvms | grep -w "$1" > /dev/null; then
    echo "ERROR: No existe ninguna máquina con el nombre de origen"
    exit 1
fi

#Comprobar que no existe la maquina clon
if vim-cmd vmsvc/getallvms | grep -w "$2" > /dev/null; then
    echo "ERROR: Ya existe una máquina con el nombre de destino"
    exit 1
fi

ID_ORIGEN=$(vim-cmd vmsvc/getallvms | grep -w "$1" | cut -d " " -f 1)

#Comprobar que la máquina origen tiene uno y sólo un snapshot
if vim-cmd vmsvc/get.snapshot "$ID_ORIGEN" | grep -w "childSnapshotList" > /dev/null; then
    echo "ERROR: La máquina origen tiene más de un snapshot"
    exit 1
fi

if ! vim-cmd vmsvc/get.snapshot "$ID_ORIGEN" | grep -w "id" > /dev/null; then
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

DISK_NAME_NO_EXT=$(echo "$DISK_NAME" | cut -d "." -f 1)
# fichero delta
if ! cp "$DATASTOREPATH/$1/$DISK_NAME_NO_EXT-delta.vmdk" "$DATASTOREPATH/$2/$DISK_NAME_NO_EXT-delta.vmdk"; then
    echo "ERROR: No se ha podido copiar el fichero delta del snapshot"
    exit 1
fi
 
#Cambiar la referencia del “parent disk” del fichero de definición del disco 
#que debe de apuntar al de la máquina origen (en el directorio ..) 
#Hay que cambiar el campo parentFileNameHint del fichero .vmdk por el nombre del padre en el directorio de la máquina origen
PARENT_NAME=$DATASTOREPATH/$1/$1.vmdk
PARENT_NAME_ESCAPED=$(echo "$PARENT_NAME" | sed 's/[\/&]/\\&/g')

if ! sed -i 's/parentFileNameHint=.*/parentFileNameHint='"$PARENT_NAME_ESCAPED"'/g' $DATASTOREPATH/$2/$DISK_NAME > /dev/null; then
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

#Crear fichero .vmsd
if ! touch "$DATASTOREPATH/$2/$2.vmsd"; then
    echo "ERROR: No se ha podido crear el fichero .vmsd"
    exit 1
fi

#Encoding
if ! echo ".encoding = \"UTF-8\"" >> $DATASTOREPATH/$2/$2.vmsd; then
    echo "ERROR: No se ha podido añadir el campo .encoding al fichero .vmsd"
    exit 1
fi

#Añadir el campo cloneOf0
if ! echo "cloneOf0 = \"$DATASTOREPATH/$1/$1.vmx\"" >> $DATASTOREPATH/$2/$2.vmsd; then
    echo "ERROR: No se ha podido añadir el campo cloneOf al fichero .vmsd"
    exit 1
fi

#numCloneOf
if ! echo "numCloneOf = \"1\"" >> $DATASTOREPATH/$2/$2.vmsd; then
    echo "ERROR: No se ha podido añadir el campo numCloneOf al fichero .vmsd"
    exit 1
fi

#sentinel0
if ! echo "sentinel0 = \"$DATASTOREPATH/$2/$DISK_NAME\"" >> $DATASTOREPATH/$2/$2.vmsd; then
    echo "ERROR: No se ha podido añadir el campo sentinel0 al fichero .vmsd"
    exit 1
fi

#numSentinels
if ! echo "numSentinels = \"1\"" >> $DATASTOREPATH/$2/$2.vmsd; then
    echo "ERROR: No se ha podido añadir el campo numSentinels al fichero .vmsd"
    exit 1
fi

#añadir campo snapshot0.clone0 al vmsd del padre
if ! echo "snapshot0.clone0 = \"$DATASTOREPATH/$2/$2.vmx\"" >> $DATASTOREPATH/$1/$1.vmsd; then
    echo "ERROR: No se ha podido añadir el campo snapshot0.clone0 al fichero .vmsd del padre"
    exit 1
fi

#snapshot0.numClones
if ! echo "snapshot0.numClones = \"1\"" >> $DATASTOREPATH/$1/$1.vmsd; then
    echo "ERROR: No se ha podido añadir el campo snapshot0.numClones al fichero .vmsd del padre"
    exit 1
fi
 
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
vim-cmd vmsvc/power.on "$ID_CLON" &

# Hay que obtener el ID de la pregunta de la máquina
sleep 1         #Añadir delay
QUESTION_ID=$(vim-cmd vmsvc/message "$ID_CLON" | grep "Virtual machine message" | cut -d " " -f 4 | cut -d ":" -f 0)

# Hay que responder a la pregunta de la máquina  "I Moved It"
vim-cmd vmsvc/message "$ID_CLON" "$QUESTION_ID" 1

#Apagar máquina
if ! vim-cmd vmsvc/power.off "$ID_CLON"; then
    echo "ERROR: No se ha podido apagar la máquina clon"
    exit 1
fi
echo "Máquina clon apagada correctamente"
