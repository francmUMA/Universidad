enable
configure terminal

interface GigabitEthernet0/0
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

interface GigabitEthernet8/0.511
encapsulation dot1Q 511
ip address 192.168.2.1 255.255.255.252
exit

interface GigabitEthernet9/0.512
encapsulation dot1Q 512
ip address 192.168.2.14 255.255.255.252
exit

exit
copy running-config startup-config

exit