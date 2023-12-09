#!/bin/bash
# lsscsi/lsblk ---- Muestra información sobre los dispositivos SCSI

# Particionar todos los discos en RAID  ---- 0xfd = Linux RAID
for i in /dev/sd[b-g]; do echo ",,0xfd" | sfdisk -uS -L "${i}"; done

# Crear RAID 5 ---- el device se llama raid_seqaccess
mdadm --create --verbose /dev/md/raid_seqaccess --chunk=512K --level=raid5 --raid-devices=6 /dev/sd[bcdefg]1

# Verificar estado
# mdadm --detail /dev/md/raid_seqaccess

# Para borrar un RAID se necesita eliminar la cabecera de los discos que forman el RAID
# mdadm --stop /dev/md/raid_seqaccess
# mdadm --zero-superblock /dev/sd[bcdefg]1

# Ahora vamos a transformar el device RAID en un volumen físico para LVM
# --dataalignment 2560k ---- 5 * 512k = 2560k ---- 5 = nivel del raid, 512k = tamaño del chunk
# Esto sirve para poder alinear de una forma óptima el volumen físico con el RAID lo que permite mantener el rendimiento
pvcreate -v --dataalignment 2560k /dev/md/raid_seqaccess

# Listar volumenes físicos
# pvs / pvdisplay

# Crear grupo de volumenes de nombre VG_seqaccess
vgcreate -v VG_seqaccess /dev/md/raid_seqaccess

# Crear un volumen lógico dentro del grupo de volumenes
# -L 5G ---- tamaño del volumen
# -n LV_bigfiles ---- nombre del volumen
# -r auto ---- número de bloques que se leen anticipadamente
lvcreate -v -r auto -L 5G -n LV_bigfiles VG_seqaccess

# Dos formas de acceso al volumen lógico
# ls -l /dev/VG_seqaccess/LV_bigfiles
# ls -l /dev/mapper/VG_seqaccess-LV_bigfiles

# Eliminar objetos creados con LVM
# lvremove /dev/VG_seqaccess/LV_bigfiles
# vgremove VG_seqaccess
# pvremove /dev/md127

## CONFIGURACION TARGET SCSI
# Arrancar el servicio en el boot
systemctl enable target.service
systemctl start target.service

# Parar el daemon de firewall ---- Provoca lentitud en el acceso a los discos
systemctl disable firewalld
systemctl stop firewalld

## ------ Dentro de targetcli ------ ##
# Crear un backstore de tipo block ---- No pasa por RAM y con escritura write-through
cd /backstores/block
create dev=/dev/VG_seqaccess/LV_bigfiles name=LV_bigfiles

# Crear un target
cd /iscsi
create wwn=iqn.2020-01.es.uma.storage:target16-040

# Se puede borrar con delete
# delete iqn.2020-01.es.uma.storage:target16-040

# Crear un LUN
cd /iscsi/iqn.2020-01.es.uma.storage:target16-040/tpg1/luns
create storage_object=/backstores/block/LV_bigfiles

# Crear una ACL 
cd /iscsi/iqn.2020-01.es.uma.storage:target16-040/tpg1/acls
create wwn=iqn.2020-01.es.uma.storage:nfs16-042
create wwn=iqn.2020-01.es.uma.storage:nfs16-043
# Para la correccion
create wwn=iqn.2020-01.es.uma.storage:nfs31-194