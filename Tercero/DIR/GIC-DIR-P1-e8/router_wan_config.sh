enable
configure terminal

interface GigabitEthernet0/0
no shutdown
exit

interface GigabitEthernet1/0
no shutdown
exit

interface GigabitEthernet2/0
no shutdown
exit

interface GigabitEthernet8/0
no shutdown
exit

interface GigabitEthernet9/0
no shutdown
exit

interface GigabitEthernet0/0.510
encapsulation dot1Q 510
ip address 192.168.0.10 255.255.255.252
exit

interface GigabitEthernet2/0.509
encapsulation dot1Q 509
ip address 192.168.0.6 255.255.255.252
exit

interface GigabitEthernet8/0
ip address 192.168.2.1 255.255.255.252
exit

interface GigabitEthernet9/0
ip address 192.168.2.14 255.255.255.252
exit

interface GigabitEthernet1/0
ip address 192.168.0.18 255.255.255.252
exit

exit
copy running-config startup-config

exit

#Routing dinamico
enable
configure terminal

router eigrp 314
no auto-summary
network 192.168.0.8 0.0.0.3
network 192.168.0.4 0.0.0.3
network 192.168.2.0 0.0.0.3
network 192.168.2.12 0.0.0.3
network 192.168.0.16 0.0.0.3
exit
exit
copy running-config startup-config

exit