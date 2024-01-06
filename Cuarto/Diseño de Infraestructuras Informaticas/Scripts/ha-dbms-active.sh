#!/bin/bash
# Detectar caídas del servidor vecino para arrancar el mysql en la máquina donde se ejecuta este script
# Antes de activar mysql hay que cambiar la ip de la máquina por la flotante
# Se indica la ip flotante y la ip vecina por parámetro

IP_FLOTANTE=$1
NETMASK=255.255.255.0

# Se ejecuta al arranque del sistema
# Se añade la ip flotante al device ens160
# Primero hay que esperar a que la ip flotante esté desactivada
# Establecer la ip que queremos

# Esperar a que la ip flotante esté desactivada
while ping -c 1 "$IP_FLOTANTE" > /dev/null
do
    sleep 1
done

# Una vez desactivada, se añade al device
ip addr add "$IP_FLOTANTE"/20 dev ens32