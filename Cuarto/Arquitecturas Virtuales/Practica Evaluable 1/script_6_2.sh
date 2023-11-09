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
    exit 1
fi

#Listar todas las máquinas para comprobar que el clon está disponible
vim-cmd vmsvc/getallvms

#Comprobar que arranca el clon
echo "Arrancando la máquina..."
ID=$(vim-cmd vmsvc/getallvms | grep "$2" | cut -d " " -f 1)
if ! vim-cmd vmsvc/power.on "$ID"; then
    echo "ERROR: No se ha podido arrancar la máquina"
    exit 1
fi

#Apagar el clon
echo "Apagando la máquina..."
if ! vim-cmd vmsvc/power.off "$ID"; then
    echo "ERROR: No se ha podido apagar la máquina"
    exit 1
fi