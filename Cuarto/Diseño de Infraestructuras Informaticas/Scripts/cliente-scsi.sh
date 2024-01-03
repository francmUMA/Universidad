#!/bin/bash
# Script para configurar cliente iSCSI en los servidores NFS

# Modificar el IQN de los clientes
echo "InitiatorName=iqn.2020-01.es.uma.storage:nfs16-042" > /etc/iscsi/initiatorname.iscsi
echo "InitiatorName=iqn.2020-01.es.uma.storage:nfs16-043" > /etc/iscsi/initiatorname.iscsi
service iscsid restart

# Modificar el archivo /etc/iscsi/iscsid.conf y cambiar node.startup a automatic
rc-update add iscsid

# Descubrir los targets
iscsiadm --mode discovery --type sendtargets --portal 10.0.16.40 -o new
# Queda almacenada y se puede ver con:
# iscsiadm --mode node

# Establecer la sesion con  el servidor
iscsiadm --mode node --portal=10.0.16.40 --targetname iqn.2020-01.es.uma.storage:target16-040 --login

# Comprobar que se ha establecido la sesion
#iscsiadm -m session

# Si queremos desloguearnos se realiza con el siguiente comando
#iscsiadm --mode node --portal=10.0.16.40 \ --targetname iqn.2020-01.es.uma.storage:target16-040 --logout

# Si tenemos algún LUN en modo manual, se debe cambiar por automatic
iscsiadm --mode node --portal=10.0.16.40 --targetname iqn.2020-01.es.uma.storage:target16-040 -o update -n node.conn[0].startup -v automatic

## OCFS2 ##
# Cambiar el nombre del cluster en /etc/conf.d/o2cb
# Añadir configuracion a cada nodo ---- MUY IMPORTANTE QUE SEA EL MISMO ORDEN EN AMBOS NODOS
o2cb add-cluster mycluster16040-
o2cb add-node mycluster16040 nfs-16-42 --ip 10.0.16.42
o2cb add-node mycluster16040 nfs-16-43 --ip 10.0.16.43

# Hay que añadir las siguientes lineas a  /etc/fstab ya que ocfs2 necesita dos puntos de montaje en /sys
none /sys/kernel/config configfs defaults 0 0
none /sys/kernel/dlm ocfs2_dlmfs defaults 0 0
rc-update add o2cb
service o2cb restart

# Crear el sistema de ficheros sobre el LUN ---- SOLO SE HACE EN UN NODO
mkfs.ocfs2 --node-slots 4 --label "myCFS16040" --cluster-name=mycluster16040 --cluster-stack=o2cb /dev/sdb

# Montar el sistema de ficheros en /clusterfs
mkdir /clusterfs
mount /clusterfs #Obviamente después de editar el fichero fstab

# Reescan de los dispositivos iSCSI
iscsiadm -m session --rescan
