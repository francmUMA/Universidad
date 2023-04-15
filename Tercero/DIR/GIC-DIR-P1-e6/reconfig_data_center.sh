enable
configure terminal


interface FastEthernet 0/0.501
ip address 10.3.0.1 255.255.254.0
exit

interface FastEthernet 0/0.502
ip address 10.3.2.1 255.255.254.0
exit

interface FastEthernet 0/0.503
ip address 10.3.4.1 255.255.254.0
exit

interface FastEthernet 0/0.504
ip address 10.3.6.1 255.255.254.0
exit

interface FastEthernet 0/0.505
ip address 10.3.8.1 255.255.254.0
exit

interface FastEthernet 0/0.506
ip address 10.3.10.1 255.255.254.0
exit

interface FastEthernet 0/0.507
ip address 10.3.12.1 255.255.254.0
exit

interface FastEthernet 0/0.508
ip address 10.3.14.1 255.255.254.0
exit

ip dhcp pool pool501
no default-router 10.1.0.1
network 10.3.0.0 255.255.254.0
default-router 10.3.0.1
exit

ip dhcp pool pool502
no default-router 10.1.2.1
network 10.3.2.0 255.255.254.0
default-router 10.3.2.1
exit

ip dhcp pool pool503
no default-router 10.1.4.1
network 10.3.4.0 255.255.254.0
default-router 10.3.4.1
exit

ip dhcp pool pool504
no default-router 10.1.6.1
network 10.3.6.0 255.255.254.0
default-router 10.3.6.1
exit

ip dhcp pool pool505
no default-router 10.1.8.1
network 10.3.8.0 255.255.254.0
default-router 10.3.8.1
exit

ip dhcp pool pool506
no default-router 10.1.10.1
network 10.3.10.0 255.255.254.0
default-router 10.3.10.1
exit

no ip dhcp excluded-address 10.1.0.1
no ip dhcp excluded-address 10.1.2.1
no ip dhcp excluded-address 10.1.4.1
no ip dhcp excluded-address 10.1.6.1
no ip dhcp excluded-address 10.1.8.1
no ip dhcp excluded-address 10.1.10.1
no ip dhcp excluded-address 10.1.12.1
no ip dhcp excluded-address 10.1.12.2
no ip dhcp excluded-address 10.1.14.1
no ip dhcp excluded-address 10.1.14.2

ip dhcp excluded-address 10.3.0.1
ip dhcp excluded-address 10.3.2.1
ip dhcp excluded-address 10.3.4.1
ip dhcp excluded-address 10.3.6.1
ip dhcp excluded-address 10.3.8.1
ip dhcp excluded-address 10.3.10.1
ip dhcp excluded-address 10.3.12.1
ip dhcp excluded-address 10.3.12.2
ip dhcp excluded-address 10.3.14.1
ip dhcp excluded-address 10.3.14.2

exit
copy running-config startup-config

exit
