enable
conf t

interface FastEthernet 0/1
switchport mode trunk
exit

interface FastEthernet 0/2
switchport mode trunk
exit

interface FastEthernet 0/3
switchport mode trunk
exit

interface FastEthernet 0/4
switchport mode trunk
exit

exit
copy running-config startup-config

exit

enable
conf t

vtp domain paco-data-center
vtp mode client
vtp password password
vtp version 2

exit 
copy running-config startup-config

exit
