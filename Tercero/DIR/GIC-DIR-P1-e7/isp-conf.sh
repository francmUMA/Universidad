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