#!/bin/bash
# Detectar caídas del servidor vecino para arrancar el mysql en la máquina donde se ejecuta este script
# Antes de activar mysql hay que cambiar la ip de la máquina por la flotante
# Se indica la ip flotante y la ip vecina por parámetro

IP_FLOTANTE=$1
IP_DESTINATION=$2
NETMASK=255.255.255.0

# Consultas periódicas a la máquina destino
# Si no hay respuesta, se activa el mysql
while true
do
    if ! ping -c 1 "$IP_FLOTANTE" > /dev/null
    then
        # Se cambia la ip de la máquina por la flotante
        ifconfig ens160 down
        ifconfig ens160 "$IP_FLOTANTE" netmask "$NETMASK"
        ifconfig ens160 up

        # Cuando vuelva a detectarse la máquina destino, se desactiva la ip
        while ! ping -c 1 "$IP_DESTINATION" > /dev/null
        do
            sleep 1
        done

        # Se reinicia el interfaz de red
        ifconfig ens160 down
        ifconfig ens160 up
    fi
    sleep 1
done