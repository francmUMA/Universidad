interface FastEthernet 0/0
no shutdown
exit

interface FastEthernet 0/0.400
encapsulation dot1Q 400
ip address 10.0.50.1 255.255.252.0
exit

interface FastEthernet 0/0.401
encapsulation dot1Q 401
ip address 10.0.54.1 255.255.254.0
exit

interface FastEthernet 0/0.402
encapsulation dot1Q 402
ip address 10.0.56.1 255.255.254.0
exit

interface FastEthernet 0/0.403
encapsulation dot1Q 403
ip address 10.0.58.1 255.255.254.0
exit

interface FastEthernet 0/0.404
encapsulation dot1Q 404
ip address 10.0.60.1 255.255.254.0
exit

interface FastEthernet 0/0.405
encapsulation dot1Q 405
ip address 10.0.62.1 255.255.255.0
exit

interface FastEthernet 0/0.406
encapsulation dot1Q 406
ip address 10.0.63.1 255.255.255.0
exit

interface FastEthernet 0/0.407
encapsulation dot1Q 407
ip address 10.0.64.1 255.255.255.128	
exit


ip dhcp pool pool400
network 10.0.50.0 255.255.252.0
default-router 10.0.50.1
exit

ip dhcp pool pool401
network 10.0.54.0 255.255.254.0
default-router 10.0.54.1
exit

ip dhcp pool pool402
network 10.0.56.0 255.255.254.0
default-router 10.0.56.1
exit

ip dhcp pool pool403
network 10.0.58.0 255.255.254.0
default-router 10.0.58.1
exit

ip dhcp pool pool404
network 10.0.60.0 255.255.254.0
default-router 10.0.60.1
exit

ip dhcp pool pool405
network 10.0.62.0 255.255.255.0
default-router 10.0.62.1
exit

ip dhcp pool pool406
network 10.0.63.0 255.255.255.0
default-router 10.0.63.1
exit

ip dhcp pool pool407
network 10.0.64.0 255.255.255.128
default-router 10.0.64.1
exit

ip dhcp excluded-address 10.0.50.1
ip dhcp excluded-address 10.0.54.1
ip dhcp excluded-address 10.0.56.1
ip dhcp excluded-address 10.0.58.1
ip dhcp excluded-address 10.0.60.1
ip dhcp excluded-address 10.0.62.1
ip dhcp excluded-address 10.0.63.1
ip dhcp excluded-address 10.0.64.1



