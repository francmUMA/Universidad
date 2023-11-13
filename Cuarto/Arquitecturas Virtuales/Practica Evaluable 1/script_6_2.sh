#!/bin/sh
#!/bin/sh
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi
#Script 6.2:
#Creación de un full clone de una VM existente en cli
#Directorio donde se ubican las máquinas
#Sustituir por el directorio de trabajo en cada caso
DATASTOREPATH=/vmfs/volumes/datastore1/mv-dest

#Imprimir su uso
if [ ! "$#" -gt "0" ]; then
    echo "Para poder ejecutar el script es necesario introducir algunos parámetros"
    echo "sh script_6_2.sh <nombre_maquina> <nombre_maquina_clon>"
    echo "  nombre_maquina: nombre de la máquina a clonar"
    echo "  nombre_maquina_clon: nombre de la máquina clon"
    exit 0
fi

#Comprobar que existe la máquina a clonar
if ! vim-cmd vmsvc/getallvms | grep "$1"; then
    echo "ERROR: No existe ninguna máquina con ese nombre"
    exit 1
fi

#Comprobar que no existe la maquina clon
if vim-cmd vmsvc/getallvms | grep "$2"; then
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
ID=$(vim-cmd vmsvc/getallvms | grep "$2" | cut -d " " -f 1)
if ! vim-cmd vmsvc/power.on "$ID" >> /dev/null; then
    echo "ERROR: No se ha podido arrancar la máquina"
    exit 1
fi
echo "Máquina arrancada correctamente"

#Apagar el clon
echo "Apagando la máquina..."
if ! vim-cmd vmsvc/power.off "$ID" >> /dev/null; then
    echo "ERROR: No se ha podido apagar la máquina"
    exit 1
fi
echo "Máquina apagada correctamente"