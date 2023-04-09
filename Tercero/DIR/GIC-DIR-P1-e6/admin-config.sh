#Configuracion de los switches para acceso desde la vlan 600
enable
configure terminal

interface vlan600
ip address 192.168.1.16 255.255.255.0

exit
exit
copy running-config startup-config

exit

#Configuración del router para añadir de forma seguro éste a la vlan 600. (Oficinas)
enable
configure terminal

ip access-list extended admin-in
permit tcp 192.168.1.2 0.0.0.0 host 192.168.1.1 eq 22
exit
ip access-list extended admin-out
permit tcp host 192.168.1.1 eq 22 192.168.1.2 0.0.0.0 established
exit
interface FastEthernet0/0.600
encapsulation dot1Q 600
ip address 192.168.1.1 255.255.255.0
ip access-group admin-in in
ip access-group admin-out out
exit
exit

#Configuración del router para añadir de forma seguro éste a la vlan 600. (Data-Center)
enable
configure terminal

ip access-list extended admin-in
permit tcp 192.168.1.2 0.0.0.0 host 192.168.1.11 eq 22
exit
ip access-list extended admin-out
permit tcp host 192.168.1.11 eq 22 192.168.1.2 0.0.0.0 established
exit
interface FastEthernet0/0.600
encapsulation dot1Q 600
ip address 192.168.1.11 255.255.255.0
ip access-group admin-in in
ip access-group admin-out out
exit
exit

#Añadir acl al servicio ssh para el acceso a través del puerto 22
enable
configure terminal

ip access-list extended ssh-in
permit tcp 192.168.1.0 0.0.0.255 any eq 22
exit
line vty 0 4
access-class ssh-in in
login local
transport input ssh
exit
exit

#Habilitación de ssh
enable
configure terminal

enable secret password_enable
line vty 0 15
password password_enable
login
exit
service password-encryption
ip domain-name paconet.com
crypto key generate rsa
1024

username admin secret password_admin
line vty 0 15
transport input ssh
login local
exit
exit
copy running-config startup-config

exit


