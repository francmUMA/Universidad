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

ip route 0.0.0.0 0.0.0.0 80.1.255.254

exit
copy running-config startup-config

exit