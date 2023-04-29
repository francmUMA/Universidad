interface FastEthernet 0/0
no shutdown
exit

interface FastEthernet 0/0.400
encapsulation dot1Q 400
ip address 10.0.48.1 255.255.252.0
exit

interface FastEthernet 0/0.401
encapsulation dot1Q 401
ip address 10.0.52.1 255.255.254.0
exit

interface FastEthernet 0/0.402
encapsulation dot1Q 402
ip address 10.0.54.1 255.255.254.0
exit

interface FastEthernet 0/0.403
encapsulation dot1Q 403
ip address 10.0.56.1 255.255.254.0
exit

interface FastEthernet 0/0.404
encapsulation dot1Q 404
ip address 10.0.58.1 255.255.254.0
exit

interface FastEthernet 0/0.405
encapsulation dot1Q 405
ip address 10.0.60.1 255.255.255.0
exit

interface FastEthernet 0/0.406
encapsulation dot1Q 406
ip address 10.0.61.1 255.255.255.0
exit

interface FastEthernet 0/0.407
encapsulation dot1Q 407
ip address 10.0.62.1 255.255.255.128	
exit

interface FastEthernet3/0
no shutdown
ip address 192.168.0.14 255.255.255.252
exit


ip dhcp pool pool400
network 10.0.48.0 255.255.252.0
default-router 10.0.48.1
exit

ip dhcp pool pool401
network 10.0.52.0 255.255.254.0
default-router 10.0.52.1
exit

ip dhcp pool pool402
network 10.0.54.0 255.255.254.0
default-router 10.0.54.1
exit

ip dhcp pool pool403
network 10.0.56.0 255.255.254.0
default-router 10.0.56.1
exit

ip dhcp pool pool404
network 10.0.58.0 255.255.254.0
default-router 10.0.58.1
exit

ip dhcp pool pool405
network 10.0.60.0 255.255.255.0
default-router 10.0.60.1
exit

ip dhcp pool pool406
network 10.0.61.0 255.255.255.0
default-router 10.0.61.1
exit

ip dhcp pool pool407
network 10.0.62.0 255.255.255.128
default-router 10.0.62.1
exit

ip dhcp excluded-address 10.0.48.1
ip dhcp excluded-address 10.0.52.1
ip dhcp excluded-address 10.0.54.1
ip dhcp excluded-address 10.0.56.1
ip dhcp excluded-address 10.0.58.1
ip dhcp excluded-address 10.0.60.1
ip dhcp excluded-address 10.0.61.1
ip dhcp excluded-address 10.0.62.1

#Configuracion de la vlan 500
enable
configure terminal

interface FastEthernet 1/0
no shutdown
exit

interface FastEthernet 1/0.500
encapsulation dot1Q 500
ip address 192.168.0.1 255.255.255.252
exit

ip dhcp excluded-address 192.168.0.1
ip dhcp excluded-address 192.168.0.2
exit
copy running-config startup-config

exit

#Configuracion de routing dinamico
enable
configure terminal

router eigrp 314
no auto-summary
network 10.0.48.0 0.0.3.255
network 10.0.52.0 0.0.1.255
network 10.0.54.0 0.0.1.255
network 10.0.56.0 0.0.1.255
network 10.0.58.0 0.0.1.255
network 10.0.60.0 0.0.0.255
network 10.0.61.0 0.0.0.255
network 10.0.62.0 0.0.0.127
network 192.168.0.8 0.0.0.3
network 192.168.0.0 0.0.0.3
network 192.168.0.12 0.0.0.3   
exit
exit
copy running-config startup-config

exit

#Configuracion del punto a punto con router wan
enable
configure terminal

interface FastEthernet 2/0
no shutdown
exit

interface FastEthernet 2/0.510
encapsulation dot1Q 510
ip address 192.168.0.9 255.255.255.252
exit
exit
copy running-config startup-config

exit




