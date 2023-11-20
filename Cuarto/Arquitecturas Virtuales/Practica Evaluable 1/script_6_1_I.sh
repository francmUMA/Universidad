#! /bin/bash
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi
#Script 6.1.I:
#Creación de una nueva VM con características mínimas desde cero en cli

#### TODO ####

# - Registrar una MV ya existente
# - Añadir NICs

###############


#Directorio donde se ubicará la maquina
DATASTOREPATH=/vmfs/volumes/datastore1/mv-dest
DISK_SIZE="1M"
NUM_NICS=0
NAME=""
#TYPE="new"

# Mostrar la ayuda en caso de que no se introduzcan los parámetros necesarios
if [ ! "$#" -gt "0" ]; then
    echo "Para poder ejecutar el script es necesario introducir algunos parámetros"
    echo "sh script_6_1.sh -name <nombre_maquina> -t <tipo_maquina> -d <disk_size> -nics <num_NICs>"
    echo "  -t: tipo de máquina (new, clone, linkedclone)"
    echo "  -d: tamaño del disco duro. Example: 6G, 10M ..."
    echo "  -nics: número de tarjetas de red"
    exit 0
fi

# Comprobar si tiene nombre
if [ "$1" = "-name" ]; then
    NAME="$2"
else
    echo "ERROR: No se ha introducido ningún nombre para la máquina"
    exit 1
fi

# Comprobar si tiene tipo
# if [ "$3" = "-t" ]; then
#     if [ "$4" = "new" ] || [ "$4" = "clone" ] || [ "$4" = "linkedclone" ]; then
#         TYPE="$4"
#     else
#         echo "ERROR: El tipo de máquina no es válido"
#         exit 1
#     fi
# fi

# Comprobar si tiene tamaño de disco
if [ "$3" = "-d" ]; then
    DISK_SIZE="$4"
elif [ "$5" = "-d" ]; then
    DISK_SIZE="$6"
elif [ "$7" = "-d" ]; then
    DISK_SIZE="$8"
fi

# Comprobar si tiene número de tarjetas de red
if [ "$3" = "-nics" ]; then
    NUM_NICS="$4"
elif [ "$5" = "-nics" ]; then
    NUM_NICS="$6"
elif [ "$7" = "-nics" ]; then
    NUM_NICS="$8"
fi


# Comprobar que no exista una con el mismo nombre
if vim-cmd vmsvc/getallvms | grep -w "$NAME"; then
    echo "ERROR: Ya existe una máquina con ese nombre"
    exit 1
fi

# TO-DO (registrar o crear según el tipo)

# Crear la máquina
echo "Creando la máquina..."
vim-cmd vmsvc/createdummyvm "$NAME" "$DATASTOREPATH"
ID=$(vim-cmd vmsvc/getallvms | grep -w "$NAME" | cut -d " " -f 1)

# Modificar el espacio de disco si es necesario
if [ ! "$DISK_SIZE" = "1M" ]; then
    echo "Modificando el espacio de disco..."
    vmkfstools -X "$DISK_SIZE" "$DATASTOREPATH/$NAME/$NAME.vmdk" > /dev/null
fi

# Modificar el número de tarjetas de red si es necesario
if [ "$NUM_NICS" -ne "0" ]; then
    echo "Modificando el número de tarjetas de red..."
    for i in $(seq 1 "$NUM_NICS"); do
        vim-cmd vmsvc/devices.createnic "$ID" "$i" "vmxnet2" "Priv-VLAN1"
    done
fi

#Listar todas las máquinas para comprobar que se ha creado
vim-cmd vmsvc/getallvms

#SÓLO SI FALLARA EL ARRANQUE
echo "Arrancando la máquina..."
if ! vim-cmd vmsvc/power.on "$ID" > /dev/null; then
    echo "Error al arrancar la máquina. Revisa el fichero de log"
    exit 1
else
    echo "La máquina ha arrancado correctamente"
fi
echo "Apagando máquina"
vim-cmd vmsvc/power.off "$ID" > /dev/null
exit 0

#¿Hay que añadir al fichero de configuración (.vmx) algún(os) campo(s) que es(son) 
#imprescindible(S) para arrancar la máquina?
#Sugerencia: intenta arrancar la máquina una vez creada y busca en el fichero 
# wmware.log por qué ha fallado el arranque