# Acl del router de la oficina
# Vlan 400-in -- Todos los pcs pueden acceder al dns y al servidor web 
ip access-list extended vlan400-in
permit udp any eq domain 10.3.12.0 0.0.1.255
permit tcp any eq www 10.3.0.0 0.0.1.255 established
permit tcp any eq www 10.3.6.0 0.0.1.255 established
exit

interface FastEthernet0/0.400
ip access-group vlan400-in in
exit
