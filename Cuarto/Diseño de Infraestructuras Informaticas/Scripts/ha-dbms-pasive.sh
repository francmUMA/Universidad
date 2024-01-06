#!/bin/bash
# Detectar caídas del servidor vecino para arrancar el mysql en la máquina donde se ejecuta este script
# Antes de activar mysql hay que cambiar la ip de la máquina por la flotante
# Se indica la ip flotante y la ip vecina por parámetro

IP_FLOTANTE=$1
IP_DESTINATION=$2

# Consultas periódicas a la máquina destino
# Si no hay respuesta, se activa el mysql
while true
do
    echo "Comprobando el estado del servidor vecino"
    if ! ping -c 1 "$IP_DESTINATION" > /dev/null
    then
        echo "Activando IP flotante"
        ip addr add "$IP_FLOTANTE"/20 dev ens32
        echo "IP flotante activada"

        # Esperar a que se active el servidor vecino
        while ! ping -c 1 "$IP_DESTINATION" > /dev/null
        do
            sleep 1
        done

        # Desactivar ip flotante
        echo "Desactivando IP flotante"
        ip addr del "$IP_FLOTANTE"/20 dev ens32
        echo "IP flotante desactivada"
    fi
    sleep 1
done