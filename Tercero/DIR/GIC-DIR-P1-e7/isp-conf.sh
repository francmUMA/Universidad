enable
configure terminal

interface GigabitEthernet0/0
no shutdown
ip address 80.1.1.128 255.255.0.0
exit

interface GigabitEthernet4/0
no shutdown
ip address 192.168.0.13 255.255.255.252
exit

interface GigabitEthernet5/0
no shutdown
ip address 192.168.0.17 255.255.255.252
exit

ip route 0.0.0.0 0.0.0.0 80.1.255.254

router eigrp 314
no auto-summary
redistribute static
network 192.168.0.12 0.0.0.3
network 192.168.0.16 0.0.0.3
exit

exit
copy running-config startup-config

exit

# Configuracion de nat
interface GigabitEthernet0/0
ip nat outside
exit

interface GigabitEthernet4/0
ip nat inside
exit

interface GigabitEthernet5/0
ip nat inside
exit

ip nat pool isp-pool 80.1.1.128  80.1.1.143 netmask 255.255.0.0

access-list 10 permit 10.0.0.0 0.255.255.255
ip nat inside source list 10 pool isp-pool overload

ip nat inside source static tcp 10.3.0.2 80 80.1.1.128 80
ip nat inside source static tcp 10.3.0.2 443 80.1.1.128 443
ip nat inside source static tcp 10.3.6.2 80 80.1.1.129 80
ip nat inside source static tcp 10.3.6.2 443 80.1.1.129 443
