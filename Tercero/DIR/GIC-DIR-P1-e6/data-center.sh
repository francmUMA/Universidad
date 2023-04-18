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

enable
config term

spanning-tree vlan 504,505,506 root secondary
spanning-tree vlan 500,501,502,503 root primary

exit
copy running-config startup-config

exit

enable
config term

spanning-tree mode rapid-pvst

exit
copy running-config startup-config

exit

interface FastEthernet 0/0
no shutdown
exit

interface FastEthernet 1/0.500
encapsulation dot1Q 500
ip address 192.168.0.2 255.255.255.252
exit

interface FastEthernet 0/0.501
encapsulation dot1Q 501
ip address 10.3.0.1 255.255.254.0
exit

interface FastEthernet 0/0.502
encapsulation dot1Q 502
ip address 10.3.2.1 255.255.254.0
exit

interface FastEthernet 0/0.503
encapsulation dot1Q 503
ip address 10.3.4.1 255.255.254.0
exit

interface FastEthernet 0/0.504
encapsulation dot1Q 504
ip address 10.3.6.1 255.255.254.0
exit

interface FastEthernet 0/0.505
encapsulation dot1Q 505
ip address 10.3.8.1 255.255.254.0
exit

interface FastEthernet 0/0.506
encapsulation dot1Q 506
ip address 10.3.10.1 255.255.254.0
exit

ip dhcp pool pool500
network 192.168.0.0 255.255.255.252
default-router 192.168.0.2
exit

ip dhcp pool pool501
network 10.3.0.0 255.255.254.0
default-router 10.3.0.1
exit

ip dhcp pool pool502
network 10.3.2.0 255.255.254.0
default-router 10.3.2.1
exit

ip dhcp pool pool503
network 10.3.4.0 255.255.254.0
default-router 10.3.4.1
exit

ip dhcp pool pool504
network 10.3.6.0 255.255.254.0
default-router 10.3.6.1
exit

ip dhcp pool pool505
network 10.3.8.0 255.255.254.0
default-router 10.3.8.1
exit

ip dhcp pool pool506
network 10.3.10.0 255.255.254.0
default-router 10.3.10.1
exit

ip dhcp excluded-address 192.168.0.1
ip dhcp excluded-address 192.168.0.2
ip dhcp excluded-address 10.3.0.1
ip dhcp excluded-address 10.3.2.1
ip dhcp excluded-address 10.3.4.1
ip dhcp excluded-address 10.3.6.1
ip dhcp excluded-address 10.3.8.1
ip dhcp excluded-address 10.3.10.1


enable
config term

interface FastEthernet 0/0.507
encapsulation dot1Q 507
ip address 10.3.12.1 255.255.254.0
exit

interface FastEthernet 0/0.508
encapsulation dot1Q 508
ip address 10.3.14.1 255.255.254.0
exit

ip dhcp excluded-address 10.3.12.1
ip dhcp excluded-address 10.3.12.2
ip dhcp excluded-address 10.3.14.1
ip dhcp excluded-address 10.3.14.2

exit
copy running-config startup-config

exit

#Configuracion de la vlan 500
enable
configure terminal

interface FastEthernet 1/0
no shutdown
exit

interface FastEthernet 1/0.500
encapsulation dot1Q 500
ip address 192.168.0.2 255.255.255.252
exit

ip dhcp excluded-address 192.168.0.1
ip dhcp excluded-address 192.168.0.2
exit
copy running-config startup-config

exit

#Configuracion de routing dinamico
enable
configure terminal

router rip
version 2
no auto-summary
network 10.0.0.0
network 192.168.0.0
exit
exit
copy running-config startup-config

exit

#Configuracion del enlace con router wan
enable
configure terminal

interface FastEthernet 2/0
no shutdown
exit

interface FastEthernet 2/0.509
encapsulation dot1Q 509
ip address 192.168.0.5 255.255.255.252
exit
exit
copy running-config startup-config

exit

