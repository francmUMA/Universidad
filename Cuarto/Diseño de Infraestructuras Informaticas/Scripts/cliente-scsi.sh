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
iscsiadm --mode node --portal=10.0.16.40 \
--targetname iqn.2020-01.es.uma.storage:target16-040 --login

# Comprobar que se ha establecido la sesion
#iscsiadm -m session

# Si queremos desloguearnos se realiza con el siguiente comando
#iscsiadm --mode node --portal=10.0.16.40 \ --targetname iqn.2020-01.es.uma.storage:target16-040 --logout

# Si tenemos algún LUN en modo manual, se debe cambiar por automatic
iscsiadm --mode node --portal=10.0.16.40 --targetname iqn.2020-01.es.uma.storage:target16-040 -o update -n node.conn[0].startup -v automatic

## OCFS2 ##
# Cambiar el nombre del cluster en /etc/conf.d/o2cb
# Añadir configuracion a cada nodo ---- MUY IMPORTANTE QUE SEA EL MISMO ORDEN EN AMBOS NODOS
o2cb add-cluster mycluster16040
o2cb add-node mycluster16040 vm-16-042 --ip 10.0.16.42
o2cb add-node mycluster16040 vm-16-043 --ip 10.0.16.43

# Hay que añadir las siguientes lineas a  /etc/fstab ya que ocfs2 necesita dos puntos de montaje en /sys
none /sys/kernel/config configfs defaults 0 0
none /sys/kernel/dlm ocfs2_dlmfs defaults 0 0
rc-update add o2cb
service o2cb restart


# * Starting OCFS2 cluster 'mycluster16040' ...
#o2cb_ctl: Configuration error discovered while populating cluster mycluster16040.  None of its nodes were considered local.  A node is considered local when its node name in the configuration matches this machine's host name.         [ !! ]
# * Stopping OCFS2 cluster 'mycluster16040' ...                            [ ok ]
# * ERROR: o2cb failed to start 
