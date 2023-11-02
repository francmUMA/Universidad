#!/bin/bash
#Arquitecturas virtuales: prácticas con vSphere 5.x ESXi
#Script 6.1.I:
#Creación de una nueva VM con características mínimas desde cero en cli

#Directorio donde se ubicará la maquina
DATASTOREPATH=/vmfs/volumes/datastore1/myfolder

#Imprimir su uso
echo Uso: "$0" "$1"

#Incluir funciones que se proporcionan

#Comprobar si existe una maquina con el mismo nombre
if  [ -d "$DATASTOREPATH/$1" ]; then
    echo "La máquina ya existe"
    exit 1
fi

#Crear la nueva máquina (sugerencia: usar vim-cmd vmsvc/createdummyvm)
vim-cmd vmsvc/createdummyvm "$1" "$DATASTOREPATH"

#Listar todas las máquinas para comprobar que se ha creado
vim-cmd vmsvc/getallvms

#SÓLO SI FALLARA EL ARRANQUE:
ID=vim-cmd vmsvc/getallvms | grep "$1" | cut -d " " -f 1

echo "Arrancando la máquina..."
if ! vim-cmd vmsvc/power.on "$ID"; then
    echo "Error al arrancar la máquina. Revisa el fichero de log"
    exit 1
else
    echo "La máquina ha arrancado correctamente"
    echo "Apagando máquina"
    vim-cmd vmsvc/power.off "$ID"
    exit 0
fi
#¿Hay que añadir al fichero de configuración (.vmx) algún(os) campo(s) que es(son) 
#imprescindible(S) para arrancar la máquina?
#Sugerencia: intenta arrancar la máquina una vez creada y busca en el fichero 
# wmware.log por qué ha fallado el arranque
