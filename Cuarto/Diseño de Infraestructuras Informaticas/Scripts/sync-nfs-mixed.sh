#!/bin/bash
# Sincronizar dos servidores NFS
# Se debe ejecutar en el nodo principal
rsync -avz --delete /frankenstein/* root@10.0.16.59:/frankenstein