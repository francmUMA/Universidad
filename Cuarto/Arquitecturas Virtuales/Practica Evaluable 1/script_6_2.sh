#!/bin/sh
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi
#Script 6.2:
#Creación de un full clone de una VM existente en cli
#Directorio donde se ubican las máquinas
#Sustituir por el directorio de trabajo en cada caso
DATASTOREPATH=/vmfs/volumes/datastore1/mv-dest
#Imprimir su uso
if [ ! "$#" -gt "1" ]; then
    echo "Para poder ejecutar el script es necesario introducir algunos parámetros"
    echo "sh script_6_2.sh <nombre_maquina> <nombre_maquina_clon>"
    echo "  nombre_maquina: nombre de la máquina a clonar"
    echo "  nombre_maquina_clon: nombre de la máquina clon"
    exit 0
fi

#Comprobar que existe la máquina a clonar
if ! vim-cmd vmsvc/getallvms | grep -w "$1"; then
    echo "ERROR: No existe ninguna máquina con ese nombre"
    exit 1
fi

#Comprobar que no existe la maquina clon
if vim-cmd vmsvc/getallvms | grep -w "$2"; then
    echo "ERROR: Ya existe una máquina con ese nombre"
    exit 1
fi

#Copiar recursivamente el directorio de la máquina origen a su destino (clon)
echo "Clonando la máquina..."
if ! cp -r "$DATASTOREPATH/$1" "$DATASTOREPATH/$2"; then
    echo "ERROR: No se ha podido clonar la máquina"
    exit 1
fi
echo "Máquina clonada correctamente"

# Renombrar los ficheros de la máquina clon
echo "Renombrando ficheros..."
if ! mv "$DATASTOREPATH/$2/$1.vmx" "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido renombrar el fichero .vmx"
    exit 1
fi

if ! mv "$DATASTOREPATH/$2/$1.vmdk" "$DATASTOREPATH/$2/$2.vmdk"; then
    echo "ERROR: No se ha podido renombrar el fichero .vmdk"
    exit 1
fi

if ! mv "$DATASTOREPATH/$2/$1-flat.vmdk" "$DATASTOREPATH/$2/$2-flat.vmdk"; then
    echo "ERROR: No se ha podido renombrar el fichero -flat.vmdk"
    exit 1
fi

if ! mv "$DATASTOREPATH/$2/$1.nvram" "$DATASTOREPATH/$2/$2.nvram"; then
    echo "ERROR: No se ha podido renombrar el fichero .nvram"
    exit 1
fi

if ! mv "$DATASTOREPATH/$2/$1.vmsd" "$DATASTOREPATH/$2/$2.vmsd"; then
    echo "ERROR: No se ha podido renombrar el fichero .vmsd"
    exit 1
fi
echo "Ficheros renombrados correctamente"

#Modificar archivo .vmx
echo "Modificando el fichero .vmx..."

#Hay que cambiar el displayName, scsi0:0.fileName y nvram
# Modificar el displayName
if ! sed -i "s/displayName = \"$1\"/displayName = \"$2\"/g" "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido modificar el displayName"
    exit 1
fi

# Modificar el scsi0:0.fileName
if ! sed -i "s/scsi0:0.fileName = \"$1.vmdk\"/scsi0:0.fileName = \"$2.vmdk\"/g" "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido modificar el scsi0:0.fileName"
    exit 1
fi

# Modificar el nvram
if ! sed -i "s/nvram = \"$1.nvram\"/nvram = \"$2.nvram\"/g" "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido modificar el nvram"
    exit 1
fi

echo "Fichero .vmx modificado correctamente"

#Modificar archivo .vmdk
echo "Modificando el fichero .vmdk..."

#Hay que cambiar el nombre de extend description
# Modificar el nombre de extend description
if ! sed -i "s/$1/$2/g" "$DATASTOREPATH/$2/$2.vmdk"; then
    echo "ERROR: No se ha podido modificar el nombre de extend description"
    exit 1
fi

#Registar la máquina clon (ESTO ES IMPRESCINDIBLE)
echo "Registrando la máquina..."
if ! vim-cmd solo/registervm "$DATASTOREPATH/$2/$2.vmx"; then
    echo "ERROR: No se ha podido registrar la máquina"
    #Borrar la máquina clon
    echo "Borrando la máquina..."
    if ! rm -rf "$DATASTOREPATH/$2"; then
        echo "ERROR: No se ha podido borrar la máquina"
        exit 1
    fi
    echo "Máquina borrada correctamente"
    exit 1
fi
echo "Máquina registrada correctamente"

#Listar todas las máquinas para comprobar que el clon está disponible
vim-cmd vmsvc/getallvms

#Comprobar que arranca el clon
echo "Arrancando la máquina..."
ID=$(vim-cmd vmsvc/getallvms | grep -w "$2" | cut -d " " -f 1)

vim-cmd vmsvc/power.on "$ID" &> /dev/null

# Responder a la pregunta de si se ha movido o copiado
vim-cmd vmsvc/message "$ID"

#Apagar el clon
echo "Apagando la máquina..."
if ! vim-cmd vmsvc/power.off "$ID" >> /dev/null; then
    echo "ERROR: No se ha podido apagar la máquina"
    exit 1
fi
echo "Máquina apagada correctamente"
