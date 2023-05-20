# Acl del router de la oficina

# VLAN 400--Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina
no ip access-list extended vlan400-in
ip access-list extended vlan400-in
permit udp 10.0.48.0 0.0.3.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.48.0 0.0.3.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.48.0 0.0.3.255 10.3.6.0 0.0.1.255 eq www
end
write

exit


interface FastEthernet0/0.400
ip access-group vlan400-in in
end
write

# VLAN 401--Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlan401-in
ip access-list extended vlan401-in
permit udp 10.0.52.0 0.0.1.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.52.0 0.0.1.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.52.0 0.0.1.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.401
ip access-group vlan401-in in
end
write

exit

# VLAN 402--Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlan402-in
ip access-list extended vlan402-in
permit udp 10.0.54.0 0.0.1.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.54.0 0.0.1.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.54.0 0.0.1.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.402
ip access-group vlan402-in in
end
write

exit

# VLAN 403--Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlan403-in
ip access-list extended vlan403-in
permit udp 10.0.56.0 0.0.1.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.56.0 0.0.1.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.56.0 0.0.1.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.403
ip access-group vlan403-in in
end
write

exit

# VLAN 404(H) -- Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlanH-in
ip access-list extended vlanH-in
permit udp 10.0.58.0 0.0.1.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.58.0 0.0.1.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.58.0 0.0.1.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.404
ip access-group vlanH-in in
end
write

exit

# VLAN 405(B) -- Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlanB-in
ip access-list extended vlanB-in
permit udp 10.0.60.0 0.0.0.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.60.0 0.0.0.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.60.0 0.0.0.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.405
ip access-group vlanB-in in
end
write

exit

# VLAN 406(G) -- Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlanG-in
ip access-list extended vlanG-in
permit udp 10.0.61.0 0.0.0.255 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.61.0 0.0.0.255 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.61.0 0.0.0.255 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.406
ip access-group vlanG-in in
end
write

exit

# VLAN 407(D) -- Solo dispositivos que esten en esa vlan pueden acceder a los servidores de la oficina

enable

configure terminal


no ip access-list extended vlanD-in
ip access-list extended vlanD-in
permit udp 10.0.62.0 0.0.0.127 10.3.12.0 0.0.1.255 eq domain
permit tcp 10.0.62.0 0.0.0.127 10.3.0.0 0.0.1.255 eq www
permit tcp 10.0.62.0 0.0.0.127 10.3.6.0 0.0.1.255 eq www
end

configure terminal



interface FastEthernet0/0.407
ip access-group vlanD-in in
end
write

exit

#VLAN DNS-INT
no ip access-list extended vlanDNS-INT-in
ip access-list extended vlanDNS-INT-in
permit udp 10.3.12.0 0.0.1.255 eq domain 10.0.48.0 0.0.15.255
permit tcp any 10.3.0.0 0.0.1.255 eq www
permit tcp any 10.3.6.0 0.0.1.255 eq www
end
write